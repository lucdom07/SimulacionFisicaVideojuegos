#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include <iostream>
#include <unordered_map>
#include "Bullet.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "WhirlGenerator.h"
#include "ExplosionGenerator.h"
#include "ForceRegistry.h"

class Level :
    public Scene
{
public:

    struct BulletConfig {
        float rVel;
        float mass;
        float gravity;
    };

    explicit Level(std::string name) : Scene(std::move(name)), currP(nullptr), partsReg(nullptr) {
        configs.insert({ shoot1, BulletConfig{350.f, 3.56f, 9.81f} });
        configs.insert({ shoot2, BulletConfig{120.f, 1000.f, 9.81f} });
    }

    void init() override {
        partsReg = new ForceRegistry();

        // CREACIÓN PARTÍCULAS
        parts.push_back(new Particle(Vector3D(10.f, 0.f, 0.f), Vector3D(), Vector3D(1.f, 0.f, 1.f), 10.f, -1, 2.f));
        parts.push_back(new Particle(Vector3D(20.f, 0.f, 0.f), Vector3D(), Vector3D(0.f, 1.f, 0.f), 1.f, -1, 2.f));

        // CREACIÓN SISTEMAS DE PARTÍCULAS
        GeneratorConfig fire;
        fire = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.001f, 0.0001f, 0.001f), // dirección velocidad
                12.f, 3.f, //magnitud velocidad
                5.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.1f, 0.2f, //color verde
                0.f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            200.f, // masa
            0.2f, // tiempo de generación
            5, // media partículas
            1, // varianza partículas
            2.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem());
        partSys[0]->addParticleGen(new ParticleGenerator(fire));

        GeneratorConfig snow;
        snow = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, -1.f, 0.f), Vector3D(0.001f, 0.0001f, 0.001f), // dirección velocidad
                12.f, 3.f, //magnitud velocidad
                3.f, 0.5f, //vida
                1.f, 0.1f, //tamaño
                1.f, 0.01f, // color rojo
                1.f, 0.01f, //color verde
                1.f, 0.001f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            1.f, // masa
            0.3f, // tiempo de generación
            20, // media partículas
            1, // varianza partículas
            10.f, //radio de emisión
            physx::PxTransform(Vector3(-40,50,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem());
        partSys[1]->addParticleGen(new ParticleGenerator(snow));

        GeneratorConfig water;
        water = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(-1.f, 0.f, 0.f), Vector3D(0.001f, 0.0001f, 0.001f), // dirección velocidad
                2.f, 0.1f, //magnitud velocidad
                5.f, 0.5f, //vida
                1.f, 0.2f, //tamaño
                0.f, 0.01f, // color rojo
                0.2f, 0.1f, //color verde
                0.9f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            1.f, // masa
            0.4f, // tiempo de generación
            25, // media partículas
            1, // varianza partículas
            10.f, //radio de emisión
            physx::PxTransform(Vector3(-40,0,0)) //transform del emisor
        };
        partSys.push_back(new ParticleSystem());
        partSys[2]->addParticleGen(new ParticleGenerator(water));

        // CREACIÓN FUERZAS
        partsWind = new WindGenerator(Vector3D(1000.f, 1000.f, 1000.f), Vector3D(10.f, 0.f, 0.f), Vector3D(0.f, 0.f, -90.f), 20.f);
        partsReg->registerPair(parts[0], partsWind);
        partsReg->registerPair(parts[1], partsWind);
        partsReg->setForceState(partsWind, false);
        forces.push_back(partsWind);

        whirl = new WhirlGenerator(Vector3D(50.f, 50.f, 50.f), Vector3D(0.f, 0.f, 0.f), 13.f);
        partSys[0]->addForce(whirl);
        partSys[0]->setForceGenState(whirl, false);
        forces.push_back(whirl);

        exp = new ExplosionGenerator(Vector3D(40.f, 40.f, 40.f), Vector3D(-20.f, 0.f, -20.f), 40.f, 40.f, 15.f);
        partSys[0]->addForce(exp);
        partSys[0]->setForceGenState(exp, false);
        forces.push_back(exp);
    }

    void update(double dt) override {
        for (ParticleSystem* s : partSys) {
            s->update(dt);
        }
        partsReg->applyForce(dt);
        for (Particle* p : parts) {
            p->integrateSemiEuler(dt);
        }
        for (Bullet* p : proyectiles) {
            p->integrateSemiEuler(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == shoot1 || key == shoot2) {
            instantiateBullet(key);
        }
        else if (key == 'z') {
            partsReg->setForceState(partsWind, true);
        }
        else if (key == 'x') {
            partSys[0]->setForceGenState(whirl, !partSys[0]->getForceGenState(whirl));
        }
        else if (key == 'c') {
            partSys[0]->setForceGenState(exp, !partSys[0]->getForceGenState(exp));
        }
    }

    void cleanup() override {
        for (Particle* p : parts) {
            delete p;
        }
        for (ParticleSystem* p : partSys) {
            delete p;
        }
        for (Bullet* p : proyectiles) {
            delete p;
        }
    }

    void instantiateBullet(unsigned char key) {
        Camera* camera = GetCamera();
        BulletConfig chosen = configs[key];
        Vector3D cameraPos = Vector3D(camera->getTransform().p);
        currP = new Bullet(cameraPos + camera->getDir() * shootDistance, camera->getDir() * chosen.rVel, chosen.mass, chosen.gravity);
        proyectiles.push_back(currP);
    }

private:
    const char shoot1 = 'p';
    const char shoot2 = 'o';

    // Distancia de la creación del proyectil a la cámara para que el proyectil no tape la cámara
    const float shootDistance = 5.f;

    std::unordered_map<unsigned char, BulletConfig> configs;
    std::vector<Particle*> parts;
    std::vector<Bullet*> proyectiles;
    std::vector<ParticleSystem*> partSys;
    std::vector<ForceGenerator*> forces;
    Bullet* currP;
    WindGenerator* partsWind;
    WhirlGenerator* whirl;
    ExplosionGenerator* exp;
    ForceRegistry* partsReg;
};


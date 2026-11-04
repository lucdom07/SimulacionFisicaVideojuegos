#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "GravityGenerator.h"
class GravityScene :
    public Scene
{
public:
    explicit GravityScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // CREACIÓN SISTEMAS DE PARTÍCULAS
        for (int i = 0; i < 3; i++) {
            partSys.push_back(new ParticleSystem());
        }

        // CREACIÓN GENERADORES DE PARTÍCULAS
        GeneratorConfig config;
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.05f, 0.0001f, 0.05f), // dirección velocidad
                25.f, 1.f, //magnitud velocidad
                15.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.1f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            10000.f, // masa
            0.5f, // tiempo de generación
            10, // media partículas
            1, // varianza partículas
            2.f, //radio de emisión
            physx::PxTransform(Vector3(-40.f,0,0)) //transform del emisor
        };
        partSys[0]->addParticleGen(new ParticleGenerator(config));

        config.emitTrans.p.x = 0.f;
        config.partMass = 0.1f;
        partSys[1]->addParticleGen(new ParticleGenerator(config));

        config.emitTrans.p.x = 40.f;
        config.partMass = 10000.f;
        partSys[2]->addParticleGen(new ParticleGenerator(config));

        //CREACIÓN GENERADORES DE FUERZAS
        GravityGenerator* gravGen = new GravityGenerator(9.81f);
        forces.push_back(gravGen);
        partSys[0]->addForce(gravGen);
        partSys[1]->addForce(gravGen);

        gravGen = new GravityGenerator(-5.f);
        forces.push_back(gravGen);
        partSys[2]->addForce(gravGen);
    }

    void update(double dt) override {
        for (ParticleSystem* s : partSys) {
            s->update(dt);
        }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        for (ParticleSystem* s : partSys) {
            delete s;
        }
        for (ForceGenerator* f : forces) {
            delete f;
        }
    }
private:
    std::vector<ParticleSystem*> partSys;
    std::vector<ForceGenerator*> forces;
};


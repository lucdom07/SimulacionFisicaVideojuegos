#pragma once
#include <vector>
#include <iostream>
#include "Scene.h"
#include "RenderUtils.hpp"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"

class P2_Scene :
    public Scene
{
public:
    explicit P2_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        partSys = new ParticleSystem();
        // CREACIÓN GENERADORES PARTÍCULAS
        GeneratorConfig config{
            UNIFORM, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.5f, 1.f, 0.5f), // dirección velocidad
                15.f, 20.f, //magnitud velocidad
                2.f, 5.f, //vida
                1.f, 2.f, //tamaño
                0.1f, 1.f, // color rojo
                0.1f, 1.f, //color verde
                0.1f, 1.f // color azul
            },
            GaussianConfig{}, // Configuración distribución gaussiana
            Vector3D(0.f,1.f,0.f),
            10.f, // masa
            0.2f, // tiempo de generación
            20, // media partículas
            10, // varianza partículas
            10.f, //radio de emisión
            physx::PxTransform(Vector3(0,0,0)) //transform del emisor
        };
        ParticleGenerator* partGen = new ParticleGenerator(config);
        partSys->addParticleGen(partGen);
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.05f, 0.0001f, 0.05f), // dirección velocidad
                15.f, 5.f, //magnitud velocidad
                2.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                1.f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.1f, 0.1f // color azul
            }, 
            Vector3D(0.f,1.f,0.f),
            10.f, // masa
            0.2f, // tiempo de generación
            30, // media partículas
            5, // varianza partículas
            2.f, //radio de emisión
            physx::PxTransform(Vector3(40,0,0)) //transform del emisor
        };
        partGen = new ParticleGenerator(config);
        partSys->addParticleGen(partGen);
        config = {
            GAUSSIAN, //Tipo de distribución
            UniformConfig{ // Configuración distribución uniforme
            },
            GaussianConfig{ // Configuración distribución gaussiana
                Vector3D(0.f, 1.f, 0.f), Vector3D(0.01f, 0.0001f, 0.01f), // dirección velocidad
                1.f, 0.5f, //magnitud velocidad
                4.f, 0.5f, //vida
                1.f, 0.5f, //tamaño
                0.5f, 0.1f, // color rojo
                0.3f, 0.1f, //color verde
                0.9f, 0.1f // color azul
            },
            Vector3D(0.f,1.f,0.f),
            50.f, // masa
            0.2f, // tiempo de generación
            50, // media partículas
            3, // varianza partículas
            20.f, //radio de emisión
            physx::PxTransform(Vector3(-60,0,0)) //transform del emisor
        };
        partGen = new ParticleGenerator(config);
        partSys->addParticleGen(partGen);
    }

    void update(double dt) override {
        partSys->update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        delete partSys;
    }
private:
    ParticleSystem* partSys;
};


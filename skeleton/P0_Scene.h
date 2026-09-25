#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include <iostream>
class P0_Scene : public Scene {
public:
    explicit P0_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // RETO A
        physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(2.0f));

        Vector3D u(3.0f, 1.0f, 0.0f);
        Vector3D v(0.0f, 4.0f, 0.0f);
        Vector3D w = u.cross(v);

        //Esfera roja
        uTr = physx::PxTransform(physx::PxVec3(u.normalize() * 5.0f));
        uRender = new RenderItem(sphereShape, &uTr, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        //Esfera verde
        vTr = physx::PxTransform(physx::PxVec3(v.normalize() * 5.0f));
        vRender = new RenderItem(sphereShape, &vTr, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        //Esfera azul
        wTr = physx::PxTransform(physx::PxVec3(w.normalize() * 5.0f));
        wRender = new RenderItem(sphereShape, &wTr, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
    }

    void update(double dt) override {
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
    }

    void cleanup() override {
        if (uRender) {
            uRender->release(); // Deregistra y destruye el item
            uRender = nullptr;
        }

        if (vRender) {
            vRender->release(); // Deregistra y destruye el item
            vRender = nullptr;
        }

        if (wRender) {
            wRender->release(); // Deregistra y destruye el item
            wRender = nullptr;
        }
    }

private:
    physx::PxTransform uTr;
    physx::PxTransform vTr;
    physx::PxTransform wTr;

    RenderItem* uRender = nullptr;
    RenderItem* vRender = nullptr;
    RenderItem* wRender = nullptr;
};


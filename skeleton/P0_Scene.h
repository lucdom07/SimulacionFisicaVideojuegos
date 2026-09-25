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
        physx::PxShape* sphereShape = CreateShape(physx::PxSphereGeometry(1.0f));

        Vector3D u(3.0f, 1.0f, 0.0f);
        Vector3D v(0.0f, 4.0f, 0.0f);
        Vector3D w = u.cross(v);

        ////Esfera roja
        //uTr = physx::PxTransform(physx::PxVec3(u.normalize() * 5.0f));
        //uRender = new RenderItem(sphereShape, &uTr, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

        ////Esfera verde
        //vTr = physx::PxTransform(physx::PxVec3(v.normalize() * 5.0f));
        //vRender = new RenderItem(sphereShape, &vTr, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        ////Esfera azul
        //wTr = physx::PxTransform(physx::PxVec3(w.normalize() * 5.0f));
        //wRender = new RenderItem(sphereShape, &wTr, Vector4(0.0f, 0.0f, 1.0f, 1.0f));

        // RETO B
        //Vector enemigo
        Vector3D d(0.f, 0.f, 1.f);
        
        //Vectores esferas
        std::vector<Vector3D> vSpheres;
        Vector3D vP_1(2.f, 0.f, 3.f);
        vSpheres.push_back(vP_1);
        Vector3D vP_2(-4.f, 0.f, 1.f);
        vSpheres.push_back(vP_2);
        Vector3D vP_3(0.f, 0.f, -5.f);
        vSpheres.push_back(vP_3);
        Vector3D vP_4(3.f, 0.f, 0.f);
        vSpheres.push_back(vP_4);

        //Transforms esferas
        P_1Tr = physx::PxTransform(physx::PxVec3(vP_1));
        P_2Tr = physx::PxTransform(physx::PxVec3(vP_2));
        P_3Tr = physx::PxTransform(physx::PxVec3(vP_3));
        P_4Tr = physx::PxTransform(physx::PxVec3(vP_4));

        // Obtener colores esferas
        std::vector<Vector4> sphereColors;
        for (Vector3D& v : vSpheres) {
            if (d.dot(v) > 0) sphereColors.push_back(Vector4(0.0f, 1.0f, 0.0f, 1.0f)); // verde si está delante
            else if (d.dot(v) < 0) sphereColors.push_back(Vector4(1.0f, 0.0f, 0.0f, 1.0f)); // rojo si está detrás
            else sphereColors.push_back(Vector4(1.0f, 1.0f, 0.0f, 1.0f)); // amarillo si está justo en el plano perpendicular
        }

        // RenderItem esferas
        //P_1Render = new RenderItem(sphereShape, &P_1Tr, sphereColors[0]);
        //P_2Render = new RenderItem(sphereShape, &P_2Tr, sphereColors[1]);
        //P_3Render = new RenderItem(sphereShape, &P_3Tr, sphereColors[2]);
        //P_4Render = new RenderItem(sphereShape, &P_4Tr, sphereColors[3]);

        // RETO C
        //Vectores A y B
        Vector3D a(-8.f, 1.f, -8.f);
        Vector3D b(8.f, 8.f, 8.f);

        //Transforms
        aTr = physx::PxTransform(physx::PxVec3(a));
        bTr = physx::PxTransform(physx::PxVec3(b));

        for (int i = 1; i < 11; i++) {
            Vector3D v = a + (b - a) * i * 0.1f;
            interTrans.push_back(physx::PxTransform(physx::PxVec3(v)));
        }

        //RenderItems
        aRender = new RenderItem(sphereShape, &aTr, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        bRender = new RenderItem(sphereShape, &bTr, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

        for (physx::PxTransform& trans : interTrans) {
            interRender.push_back(new RenderItem(sphereShape, &trans, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
        }
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

        if (P_1Render) {
            P_1Render->release(); // Deregistra y destruye el item
            P_1Render = nullptr;
        }

        if (P_2Render) {
            P_2Render->release(); // Deregistra y destruye el item
            P_2Render = nullptr;
        }

        if (P_3Render) {
            P_3Render->release(); // Deregistra y destruye el item
            P_3Render = nullptr;
        }

        if (P_4Render) {
            P_4Render->release(); // Deregistra y destruye el item
            P_4Render = nullptr;
        }

        if (aRender) {
            aRender->release(); // Deregistra y destruye el item
            aRender = nullptr;
        }

        if (bRender) {
            bRender->release(); // Deregistra y destruye el item
            bRender = nullptr;
        }

        for (RenderItem* r : interRender) {
            r->release(); // Deregistra y destruye el item
            r = nullptr;
        }
    }

private:
    // RETO A
    physx::PxTransform uTr;
    physx::PxTransform vTr;
    physx::PxTransform wTr;

    RenderItem* uRender = nullptr;
    RenderItem* vRender = nullptr;
    RenderItem* wRender = nullptr;

    // RETO B
    physx::PxTransform P_1Tr;
    physx::PxTransform P_2Tr;
    physx::PxTransform P_3Tr;
    physx::PxTransform P_4Tr;

    RenderItem* P_1Render = nullptr;
    RenderItem* P_2Render = nullptr;
    RenderItem* P_3Render = nullptr;
    RenderItem* P_4Render = nullptr;

    // RETO C
    physx::PxTransform aTr;
    physx::PxTransform bTr;
    std::vector<physx::PxTransform> interTrans;

    RenderItem* aRender = nullptr;
    RenderItem* bRender = nullptr;
    std::vector<RenderItem*> interRender;

};


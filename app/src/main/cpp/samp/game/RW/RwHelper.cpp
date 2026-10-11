//
// Created by x1y2z on 20.04.2023.
//

#include "RenderWare.h"
#include "game.h"

RwObject* GetFirstObjectCallback(RwObject* object, void* data) {
    *(RwObject**)(data) = object;
    return nullptr;
}

RwObject* GetFirstObject(RwFrame* frame) {
    RwObject* obj{};
    RwFrameForAllObjects(frame, GetFirstObjectCallback, &obj);
    return obj;
}

RpAtomic* GetFirstAtomic(RpClump* clump) {
    RpAtomic* atomic{};
    RpClumpForAllAtomics(clump, GetFirstAtomicCallback, &atomic);
    return atomic;
}

RpAtomic* GetFirstAtomicCallback(RpAtomic* atomic, void* data) {
    *(RpAtomic**)(data) = atomic;
    return nullptr;
}

// name not from Android
RpAtomic* SkinAtomicGetHAnimHierarchCB(RpAtomic* atomic, void* data) {
    RpHAnimHierarchy* hier = RpSkinAtomicGetHAnimHierarchy(atomic);
    if (hier) {
        *(RpHAnimHierarchy**)(data) = hier;
        return nullptr; // Found skin hierarchy! Stop enumeration.
    }
    return atomic; // Continue checking next atomic
}

RpHAnimHierarchy* GetAnimHierarchyFromSkinClump(RpClump* clump) {
    if (!clump) return nullptr;
    RpHAnimHierarchy *anim{};
    RpClumpForAllAtomics(clump, SkinAtomicGetHAnimHierarchCB, &anim);
    if (!anim) {
        // Fallback: check clump hierarchy from frames if not on first atomic
        anim = ((RpHAnimHierarchy*(*)(RpClump*))(g_libGTASA + (VER_x32 ? 0x005D10D0 + 1 : 0x6F55D4)))(clump);
    }
    return anim;
}

RpAtomic* AtomicRemoveAnimFromSkinCB(RpAtomic* atomic, void* data) {
    if (RpSkinGeometryGetSkin(RpAtomicGetGeometry(atomic))) {
        if (RpHAnimHierarchy* hier = RpSkinAtomicGetHAnimHierarchy(atomic)) {
            RtAnimAnimation*& currAnim = hier->currentAnim->pCurrentAnim;
            if (currAnim) {
                RtAnimAnimationDestroy(currAnim);
            }
            currAnim = nullptr;
        }
    }
    return atomic;
}

RpClump* RpClumpGetBoundingSphere(RpClump* clump, RwSphere* sphere, bool bUseLTM) {
    return ((RpClump * (__cdecl*)(RpClump*, RwSphere*, bool))(g_libGTASA + (VER_x32 ? 0x5D0E3C + 1 : 0x6F51F8)))(clump, sphere, bUseLTM);
}

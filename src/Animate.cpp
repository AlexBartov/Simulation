#include "Animate.h"
#include "MainSceneGL.h"
#include "MainSceneGL.h"
Animate *Animate::animation = nullptr;

Animate::Animate()
    : time(nullptr)
{
    if(!animation)
    {
        animation = this;
    }
    else delete this;
}

void Animate::addAnimator(SceneObject *object)
{
    if(exists(object))
    {
        return;
    }
    if(object->type == SPHERE)
    {
        animators.push_back(new AnimatorSphere((Sphere*) object));
    }
}

void Animate::removeAnimator(int id)
{
    for (int i = 0; i < animators.size(); i++)
    {
        if(animators[i]->getObjectId() == id)
        {
            delete animators[i];
            animators.erase(animators.begin() + i);
        }

    }
}

bool Animate::exists(SceneObject *object)
{
    int id = object->getId();
    for(Animator *animator : animators)
    {
        if(animator->getObjectId() == id)
        {
            return true;
        }
    }
    return false;
}

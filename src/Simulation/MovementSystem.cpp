#include "MovementSystem.h"

#include <Simulation/Unit.h>

MovementSystem::MovementSystem(std::shared_ptr<entt::registry> Registry, float Gravity, float AirDensity) :
    m_Gravity(Gravity),
    m_AirDensity(AirDensity)
{
    m_Registry = Registry;
}

MovementSystem::~MovementSystem()
{

}

void MovementSystem::step(double StepSize)
{
    auto MoveObjects = m_Registry->view<ID, Velocity, Position>();

    for(auto& Object : MoveObjects)
    {

        auto& ObjectVelocity = m_Registry->get<Velocity>(Object).VelocityVector;

        auto& ObjectPosition = m_Registry->get<Position>(Object).Position;

        auto& ObjectID = m_Registry->get<ID>(Object).ID;

        auto PrevPosition = ObjectPosition;

        //Changing position
        if(ObjectPosition.y > 0.0f || ObjectVelocity.y > 0.0f)
        {
            ObjectPosition += ObjectVelocity * static_cast<float>(StepSize);
            
            if(ObjectPosition.y < 0.0f)
            {
                ObjectPosition.y = 0.0f; //Maybe create func to calculate when was 0 and set position according to it
            }
        }


        //Check collision
        auto  ObjectHitIndicator = m_Registry->try_get<HitIndicator>(Object);

        if (ObjectHitIndicator != nullptr)
        {
            bool Result = checkCollision(ObjectID, PrevPosition, ObjectPosition);

            if (Result)
            {
                ObjectHitIndicator->Hit = true;
            }
        }



        //Update velocity
        {   

            if (ObjectPosition.y > 0.0f)
            {

                auto ObjectWeight = m_Registry->try_get<Weight>(Object);

                auto ObjectAerodynamic = m_Registry->try_get<Aerodynamic>(Object);

                if (ObjectWeight != nullptr && ObjectAerodynamic != nullptr)
                {
                    if (ObjectWeight->KG == 0)
                        break;


                    float Constant = (powf(ObjectVelocity.getLength(), 2) * m_AirDensity * ObjectAerodynamic->CrossSectionalArea * ObjectAerodynamic->DragCoefficient) / 2.0f;

                    Vector3<float> AirResistance = ObjectVelocity;

                    AirResistance = AirResistance.getUnitVector();

                    AirResistance *= -(1.0f * Constant) / ObjectWeight->KG;

                    ObjectVelocity += AirResistance * static_cast<float>(StepSize);
                }

                ObjectVelocity.y = ObjectVelocity.y - m_Gravity * static_cast<float>(StepSize);
            }
            else
            {
                ObjectVelocity = {0.0f, 0.0f, 0.0f};
            }
        }
    
    }
}


bool MovementSystem::checkCollision(int const ObjectID, Vector3<float> const PrevPosition, Vector3<float> const NextPosition) const
{
    if(PrevPosition == NextPosition)
        return false;

    auto ObjectsWithCollision = m_Registry->view<ID, Position, CollisionArea>();

    for(auto& Target: ObjectsWithCollision)
    {
        auto& TargetID = m_Registry->get<ID>(Target).ID;

        if(TargetID == ObjectID)
            continue;

        const auto& TargetPostion = m_Registry->get<Position>(Target).Position;

        const auto& TargetArea = m_Registry->get<CollisionArea>(Target).Radius;

        auto Temp1 = NextPosition - PrevPosition;

        auto Temp2 = PrevPosition - TargetPostion;

        auto Temp3 = cross(Temp1, Temp2);

        float Temp4 = Temp3.getLength() / Temp1.getLength();

        if (Temp4 <= TargetArea)
            return true;
        
    }

    return false;
}
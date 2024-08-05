#include "Simulation.h"

#include <Simulation/Unit.h>

#include <cmath>
#include <numbers>
#include <iostream>

Simulation::Simulation(const Arguments& Data)
{

    m_Data.Start = Data.Start;

    m_Data.Goal = Data.Goal;

    m_Data.AccuracyToHit = 0.01f;


    m_Data.StartVelocity = Data.StartVelocity;


    m_Data.Weight = Data.Weight;


    m_Data.SimStep = Data.SimStep;


    m_Registry = std::make_shared<entt::registry>();

    m_MovementSystem = std::make_shared<MovementSystem>(m_Registry);
}

Simulation::~Simulation()
{

}

void Simulation::run()
{
    m_Data.AngleOfShout = static_cast<float>(std::numbers::pi/4);

    float Min = -1.0f * static_cast<float>(std::numbers::pi/2);

    float Max = static_cast<float>(std::numbers::pi/2);



    for(int i = 0; i < m_Data.MaxCountOfSimulation; i++)
    {
        countVelocityVector();

        auto Result = runSimulation(false);

        switch (Result.SimRes)
        {
        case SimulationResult::Result::HIT:
            std::cout << "Bullet hit at " << m_Data.AngleOfShout * (180.0f / std::numbers::pi) << " degree\n";
            runSimulation(true);
            return;

        case SimulationResult::Result::UNDERSHOT:
            if (m_Data.AngleOfShout == Max) return;
            Min = m_Data.AngleOfShout;

            if (i == 0) m_Data.AngleOfShout = Max;

            else m_Data.AngleOfShout = Max -  ((Max - Min) / 2.0f);
            
            break;

        case SimulationResult::Result::OVERSHOT:
            if (m_Data.AngleOfShout == Min) return;
            Max = m_Data.AngleOfShout;

            if (i == 0) m_Data.AngleOfShout = Min;

            else m_Data.AngleOfShout = Max -  ((Max - Min) / 2.0f);
            
            break;

        }

    }

    
}


Simulation::SimulationResult Simulation::runSimulation(bool Print)
{
    double Time = 0.0;


    //Setup Bullet
    auto Bullet = m_Registry->create();

    m_Registry->emplace<ID>(Bullet, 0);

    m_Registry->emplace<Velocity>(Bullet, m_Data.VelocityVector);

    m_Registry->emplace<Position>(Bullet, m_Data.Start);

    m_Registry->emplace<HitIndicator>(Bullet, false);


    //Setup Goal
    auto Goal = m_Registry->create();

    m_Registry->emplace<ID>(Goal, 1);

    m_Registry->emplace<Position>(Goal, m_Data.Goal);

    m_Registry->emplace<CollisionArea>(Goal, m_Data.AccuracyToHit);
    
    auto& Hit = m_Registry->get<HitIndicator>(Bullet);

    auto& BulletPos = m_Registry->get<Position>(Bullet);
    
    auto& BulletVelocity = m_Registry->get<Velocity>(Bullet);

    if(Print)
    {
        std::cout << "Print data format:Time; Bullet position x, y, z; Bullet velocity x, y ,z.\n";
    }


    //Iteration
    while (true)
    {
        
        if (Print)
        {
            printf("%10.4f|%10.4f|%10.4f|%10.4f|%10.4f|%10.4f|%10.4f\n", 
            Time, 
            BulletPos.Position.x, BulletPos.Position.y, BulletPos.Position.z,
            BulletVelocity.VelocityVector.x, BulletVelocity.VelocityVector.y, BulletVelocity.VelocityVector.z);
        }

        Time += m_Data.SimStep;

        m_MovementSystem->step(m_Data.SimStep);


        if (Hit.Hit == true)
        {
            clearRegistry();
            return SimulationResult{SimulationResult::Result::HIT, 0.0f};
        }


        Vector3<float> Distance{m_Data.Goal.x - BulletPos.Position.x, m_Data.Goal.y - BulletPos.Position.y, m_Data.Goal.z - BulletPos.Position.z};

        if (Distance.x != 0 && (Distance.x / BulletVelocity.VelocityVector.x) < 0)
        {
            if (Distance.y < 0)
            {
                clearRegistry();
                return SimulationResult{SimulationResult::Result::OVERSHOT, Distance.getLength()};
            }

            else
            {
                clearRegistry();
                return SimulationResult{SimulationResult::Result::UNDERSHOT, Distance.getLength()};
            }
        }

        if (Distance.z != 0 && (Distance.z / BulletVelocity.VelocityVector.z) < 0)
        {
            if (Distance.y < 0)
            {
                clearRegistry();
                return SimulationResult{SimulationResult::Result::OVERSHOT, Distance.getLength()};
            }

            else
            {
                clearRegistry();
                return SimulationResult{SimulationResult::Result::UNDERSHOT, Distance.getLength()};
            }
        }

        if (BulletPos.Position.y <= 0.0f)
        {
            clearRegistry();
            return SimulationResult{SimulationResult::Result::UNDERSHOT, Distance.getLength()};
        }
    }
}


void Simulation::countVelocityVector()
{
    m_Data.VelocityVector = {m_Data.Goal.x - m_Data.Start.x, 0.0f, m_Data.Goal.z - m_Data.Start.z};

    m_Data.VelocityVector.y = m_Data.VelocityVector.getLength() * tanf(m_Data.AngleOfShout);

    m_Data.VelocityVector = m_Data.VelocityVector.getUnitVector() * m_Data.StartVelocity;
}


void Simulation::clearRegistry()
{
    m_Registry->clear();
}
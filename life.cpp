#include "life.h"

life::life()
{

}
void life::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    if(contact && contact->IsTouching())
    {
        GameItem* A = static_cast<GameItem*>(contact->GetFixtureA()->GetBody()->GetUserData());
        GameItem* B = static_cast<GameItem*>(contact->GetFixtureB()->GetBody()->GetUserData());


        if(impulse->normalImpulses[0]>50)
        {
            qDebug()<<impulse->normalImpulses[0];
            A->life -= impulse->normalImpulses[0];
            B->life -= impulse->normalImpulses[0];

            if(A->life <= 0)
            {
                A->life = 0;
                A->dead = true;
            }
            if(B->life <= 0)
            {
                B->life = 0;
                B->dead = true;
            }
        }
    }
}

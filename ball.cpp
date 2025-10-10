#include "ball.hpp"
#include "Methods.cpp"
#include <cmath>

float ball::l = 1.; //metto 1 per non far esplodere A
float ball::r1 = 0.5;
float ball::r2 = 1.;
float ball::mGiac = l/(r2-r1);

ball::ball(float _xo, float _yo, float _vx, float _vy, bool _collide){
    x = _xo;
    y = _yo;
    vx = _vx;
    vy = _vy;
    collide = _collide;
};

float ball::Sgn(){
    return -(y > 0) + (y < 0);

}
//in questa forma c'è qualcosa che non va, devo ricalcolare tutti i coefficienti ogni volta mentre per l'animazione sarebbe sufficiente calcolarli una volta sola. Si può ottimizzare


float ball::postCollisionM(float m){
    float B = postCollisionAngle(m);
    float m2 = mGiac * (-sgn(y));
    float m3 = (m2 + B)/(1-m2*B); //si possono invertire i segni e si ottiene un altra retta: Attenzione!
    return m3;
}
float ball::postFirstCollisionM(float m){

}
float ball::postnCollisionM(float m){}
float ball::postCollisionAngle(float m){ //non ho implementato il +,-
    float m2 = mGiac * (-(y > 0) + (y < 0));
    return std::abs((m2-m)/(1+m*m2));

}


void ball::nCollision(float mPre){      //le nCollision mi updatano i valori dell'urto
    float M = postCollisionM(mPre);
    if(sgn(y) >= 0){
        float xu = x;
        x = (-r1-y+M*x)/(M+(r2-r1)/l);
        y = M*(x-xu) + y;
        
    }
    if(sgn(y) < 0){
        float xu = x;
        x = (r1-y+M*x)/(M-(r2-r1)/l);
        y = M*(x-xu) + y;
    }

}
void ball::firstCollision(float mTan){  //tiene conto se l'urto è sopra o sotto
       //questa versione vale se la prima inizializzazione di ball è a x=0, y = y0;
        if(mTan >= 0.){                           
            x = (y - r1)/((r2-r1)/l -mTan);
            y = mTan*x + y;
            collide = 1;
        }
        if(mTan < 0.){
            x = (y + r1)/((r1-r2)/l -mTan);
            y = mTan*x + y;
            collide = 1;
        }
    }

void ball::collision(float m){
    if(x < 1e4){
        firstCollision(m);
    }else{
        nCollision(m);
    }
}

bool ball::selector(float m, bool updown){ //mi deve dare 0 se la palla esce, 1 se la palla prosegue, probabilmente si può ottimizzare: fanno la stessa cosa, cmabia solo la guardia. Ci sono anche dei problemi con il Fist impact senza ciò
    //se so da dove parte ho 2 possibili range, per updown maggiore di 0 urta contro la cosa alta
    float M;
    if(x < 1e4){
        float M = m;
    }else{
        
        float M = postCollisionM(m);}

    if(updown > 0){
       if(M*(l-x)+y > -r2 && M*(l-x) + y < r2){
        return 0;
       }
       if(M*(-x)+y > -r1 && M*(-x) + y < r1){
        return 0;
       }
       if(M*(l-x)+y < -r2 || M*(-x)+y < - r1){
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;
       }
       else{
        return 1;
    }
    }
    if(updown < 0){
        if(M*(l-x)+y > -r2 && M*(l-x)+y < r2){
            return 0;
        }
        if(M*(-x)+y > -r1 && M*(-x)+y < r1){
        return 0;
        }
        if(M*(l-x)+y > r2 || M*(-x)+y > r1){
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;    
        }
        else{return 0;}
    }}






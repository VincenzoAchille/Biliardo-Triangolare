#ifndef BALL_HPP
#define BALL_HPP

struct collisionBall{
    float x_o;
    float y_o;
    bool collide; //1 collide, 0 no
};

class ball{
    public:
    //costruttori
    ball(float x, float y, float vx, float vy, bool collide);
    ball(float x, float y, float vx, float vy);
    ball(float x, float y);
    ball();
    //manca il costruttore copia
    //metodi
    void firstCollision(float mTan); //mi genera i primi xu e yu da cui derivo la prima equazione di giacomini
    void nCollision(float m);
    void collision(float m);
    void collisionParamters(float m);
    float Sgn();
    float positionX(float t) {return t;}
    float positionY(float t, float m) {return m*(t-x) + y;}
    float postnCollisionM(float m);
    float postFirstCollisionM(float m);
    float postCollisionM(float m);
    float postCollisionAngle(float m);
    bool selector(float m, bool a, bool b);
    //setters
    static void setr1(float _r1) { r1 = _r1; }
    static void setr2(float _r2) { r2 = _r2; }
    static void setl(float _l) { l = _l; }
    //getters
    static float getr1() { return r1;}
    static float getr2() { return r2; }
    static float getl() { return l;}
    static float getmGiac() {return l/(r2 - r1);}
    float getX() {return x;}
    float getY() {return y;}
    bool getCollide(){return collide;}  //è inline
    //operazioni
    //distruttori

    private:
    float x;
    float y;
    float vx;
    float vy;
    bool collide;

    static float l; //vanno inizializzati come puntatori?
    static float r1;
    static float r2;
    static float mGiac;
};

#endif
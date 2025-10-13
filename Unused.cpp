/*inline void endingDynamics(ball &b1, float &m, float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t, sf::CircleShape &shape1, ball &bParameters, bool direction){
    
    std::cout << "endingDynamics" << '\n';
    shape1.setPosition(center[0] + b1.getX(),center[1] - b1.getY()); //da rivedere l'inizializzazione
    shape1.setFillColor(sf::Color::Cyan);
    float impact[2] = {bParameters.getX(), bParameters.getY()};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        //std::cout << a1.positionY(i, m) << ", " << a1.getX() << '\n';
        shape1.setPosition(center[0] + b1.positionX(3*t), center[1]- b1.positionY(3*t, m)); // non chiarissimo cosa faccia l'equazione di Giacomini, forse conta gia y0
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();
        //sotto non ci vorrebbe impact perchè le coordinate di impatto non sono quelle di bParameters
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 5. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 5.)){
            std::cout << "la pallina è scappata!" << '\n';
            pause();

        }else{
            t++;
        }
    }


}*/

/*inline void collidingDynamics(ball &b1, float &m, float center[2], sf::Vertex upperBound[], sf::Vertex lowerBound[], sf::RenderWindow &window, int &t,sf::CircleShape &shape1, ball &bParameters, bool direction){
// necessario passare shape by reference? e bParameters?
    std::cout << "collidyingDynamics" << '\n';
    float impact[2] = {bParameters.getX(), bParameters.getY()}; // attenzione: devo passare by reference?
        //una prima versione mi calcola solo l'impatto
        //un altra aggiorna la ball
        //ad ogni iterazione controlla se x,y position coincidono con collision -> se lo voglio fare con Dynamics è più complesso
        shape1.setPosition(center[0] + b1.getX(),center[1] - b1.getY());
        while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        shape1.setPosition(center[0] + b1.positionX(3*t), center[1]- b1.positionY(3*t)); 
        window.clear();
        window.draw(upperBound, 2, sf::Lines); //preso da Chat
        window.draw(lowerBound, 2, sf::Lines);
        window.draw(shape1);
        window.display();

        //osservazione: se il programma funziona basta avere la condizione sulle x e non anche sulle y. E'un controllo ulteriore ma perdo potenza di calcolo. Cosa vuole Giacomo?
        //std::cout << std::abs((shape1.getPosition()).x -center[0] - impact[0]) << ", " << std::abs((-shape1.getPosition()).y +center[1] -impact[1]) << '\n';
        if(std::abs((shape1.getPosition()).x -center[0] - impact[0]) < 5. && (std::abs((-shape1.getPosition()).y +center[1] -impact[1]) < 5.)){
            std::cout << "la pallina ha urtato!" << '\n';
            std::cout <<  "mPreUrto=" << m <<  ", " << b1.getX() << '\n';
            b1 = bParameters;
            std::cout << "mPostUrto=" << m <<  ", " << b1.getX() <<'\n'; //c'è un problema nel calcolo del punto d'urto
            b1.collision(direction); //quando chiamo collision ho ancora x del firstImpact
            m = b1.postCollisionM(direction);//quando chiamo questo ho ancora i punti di impatto iniziali e sto sempre nel firstImpact
            std::cout << m << ", " << b1.getX() <<'\n';

            break;
            
            
        }else{
            t++;
        }
        
    }
}*/


/*bool ball::selector(float m, bool updown, bool direction){ //mi deve dare 0 se la palla esce, 1 se la palla prosegue, probabilmente si può ottimizzare: fanno la stessa cosa, cmabia solo la guardia. Ci sono anche dei problemi con il Fist impact senza ciò
    //se so da dove parte ho 2 possibili range, per updown maggiore di 0 urta contro la cosa alta
    float M;
    if(x < 1e-2){
        M = m; 
        bool a = (M*(l-x)+y > -r2 && M*(l-x) + y < r2) && 1;
        std::cout << "sono nel caso di FirstImpact" <<'\n';
    }else{
        
        M = postCollisionM(m);
        std::cout << "sono nel caso di nImpact" << '\n';
    }
    std::cout << "updown=" << updown << ", direction=" << direction << '\n';
    if(updown == 1){
       if((M*(l-x)+y > -r2 && M*(l-x) + y < r2) && direction){   //queste sono verso dx
        std::cout << "triggeer dx " << '\n';
        return 0;
       }
       if((M*(-x)+y > -r1 && M*(-x) + y < r1) && direction){     //queste sono verso sx
        return 0;
        std::cout << "trigger sx" << '\n';
       }
       if(M*(-x)+y < - r1 && direction){    //verso sx
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;
       }
       if(M*(l-x)+y < -r2 && direction){ //verso dx
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;
       }
       
        std::cout << "return 1: updown == 1 " << '\n';
        return 1;
    }
    
    if(updown == 0){
        if((M*(l-x)+y > -r2 && M*(l-x)+y < r2) && direction){
            std::cout << "trigger dx updown=0" << '\n';
            return 0;
        }
        
        if((M*(-x)+y > -r1 && M*(-x)+y < r1) && direction){
            std::cout << "trigger sx updown=0" << '\n';
        return 0;
        }
        if((M*(-x)+y > r1) && direction){  //verso dx
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;    
        }
        if((M*(l-x)+y > r2) && direction){  //verso sx
        std::cout << "errore: la pallina non rimbalza contro il muro" << '\n';
        return 0;    
        }
        
            std::cout << "return 1: updown == 0 " << '\n';
            return 1;
    }}*/
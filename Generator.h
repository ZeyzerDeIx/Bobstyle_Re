#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

    #include "constants.h"
    #include "Debris.h"
    #include "Cloud.h"
    #include "Bobstyle.h"
    #include "usefull_fonctions.h"

    class Generator
    {
        public:

            Generator(Global_variables_container* GVC);
            ~Generator();

            void generate_entities(int type, int number = 1); //genere autant d'entités que demandé
            void set_auto_generation(bool enable); //permet d'activer ou de désactiver la génération automatique
            void clear_dead_entity(); //nettoie les entités mortes
            void manage(); //nettoie les entités mortes et fait bouger les autres
            void display(); //affiche les entités
            void manage_and_display();
            void set_debug_mode(bool enable); //permet d'activer ou de désactiver le debug mode
            void manage_collisions(Bobstyle* bobstl = nullptr); //permet de gerer les collisions entre bobstyle et les entités

            bool get_debug_mode(); //sert à savoir si le generateur est en debug mode

        private:

            Global_variables_container* m_GVC; //le pointeur vers le gvc

            std::list<Entity*> m_entities; //tableau d'entités

            bool m_debug_mode; //vrai si le debug mode est actif
            bool m_auto_gen; //vrai si la génération automatique est active

            int m_frame_counter; // compte le nombre de frame qui se sont écoulées
            int m_last_frame[MAX_ENTITY_NUMBER]; //dernier nombre de frames enregistré pour chaque entité
    };

#endif // GENERATOR_H_INCLUDED

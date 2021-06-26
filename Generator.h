#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

    #include "constants.h"
    #include "Debris.h"
    #include "Cloud.h"
    #include "Homing_missile.h"
    #include "Bobstyle.h"
    #include "usefull_fonctions.h"

    class Generator
    {
        public:

            Generator(Global_variables_container* GVC, Entity* bobstyle);
            ~Generator();

            void generate_entities(int type, int x = 0, int y = 0, Entity *target = NULL, int number = 1); //genere autant d'entités que demandé
            void set_auto_generation(bool enable); //permet d'activer ou de désactiver la génération automatique
            void clear_dead_entity(); //nettoie les entités mortes
            virtual void manage(); //nettoie les entités mortes et fait bouger les autres
            virtual void display(); //affiche les entités
            void manage_and_display();
            virtual void set_debug_mode(bool enable); //permet d'activer ou de désactiver le debug mode
            void set_clouds(bool enable); //active/désactive les nuages
            virtual void manage_collisions(Entity* enty = 0); //permet de gerer les collisions entre bobstyle et les entités

            bool get_debug_mode(); //sert à savoir si le generateur est en debug mode

            int get_type_occurences(int type); //retourne le nombre d'entité d'un type précis que possède le générateur

        protected:

            Global_variables_container* m_GVC; //le pointeur vers le gvc

            std::list<Entity*> m_entities; //tableau d'entités

            Entity* m_bobstyle; //un pointeur vers bobstyle (pour les missiles)

            bool m_debug_mode; //vrai si le debug mode est actif
            bool m_auto_gen; //vrai si la génération automatique est active
            bool m_clouds_enable; //vrai si les nuages doivent être affichés

            int m_last_frame[MAX_ENTITY_NUMBER+1]; //dernier nombre de frames enregistré pour chaque entité
    };

#endif // GENERATOR_H_INCLUDED

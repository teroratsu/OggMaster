#ifndef LINEDISPLAYER_H
#define LINEDISPLAYER_H

#include "SoundWaveDisplayer.h"
#include <SFML/Graphics.hpp>
#include <random>

class LineDisplayer: public SoundWaveDisplayer
{
    public:
        LineDisplayer(sfg::Canvas::Ptr,const unsigned int&,const unsigned int&);
        virtual ~LineDisplayer();

        void draw(float*,float,sf::Time,sf::SoundSource::Status);

    private:
        void updateSparks(float,sf::Time);

        sf::VertexArray _LinesR_b;
        sf::VertexArray _LinesR_h;
        sf::VertexArray _LinesL_b;
        sf::VertexArray _LinesL_h;

        sf::VertexArray _Sparks;
        std::pair <int,double>* _sparkTab;
        float _velocity;
        std::default_random_engine _g;//rnd generator

        const int DEFAULT_VELOCITY;
        const int DEFAULT_SPARK_NUMBER;
        int _verticalOffset;

        sfg::Canvas::Ptr _canvas;
};

#endif // LINEDISPLAYER_H

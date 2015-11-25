#ifndef LINEDISPLAYER_H
#define LINEDISPLAYER_H

#include "SoundWaveDisplayer.h"
#include <SFML/Graphics.hpp>
#include <random>

class LineDisplayer: public SoundWaveDisplayer
{
public:
    //! default ctor
    /*!
      \param c pointer to the canavs where to draw
      \param v default_velocity of sparks
      \param s_c sparks count, number of sparks to draw
    */
    LineDisplayer(sfg::Canvas::Ptr c,const unsigned int& v,const unsigned int& s_c);
    virtual ~LineDisplayer();

    //! draw function, must be called only if the canavs as been initialize
    /*!
      \param f data array, the one to work with
      \param avg average power, based on the data
      \param of playing offset
      \param s _stream status
      \sa _canvas and LineDisplayer()
    */
    void draw(float*,float,sf::Time,sf::SoundSource::Status);

private:
    //! functino called in the draw method
    /*!
      \param of playing offset, time elapsed
      \param avg average power, based on the data
    */
    void updateSparks(float avg,sf::Time of);

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

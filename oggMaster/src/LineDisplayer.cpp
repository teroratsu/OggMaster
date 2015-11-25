#include "../header/LineDisplayer.h"

LineDisplayer::LineDisplayer(sfg::Canvas::Ptr canvas, const unsigned int& v_, const unsigned int& s_c):DEFAULT_VELOCITY(v_),DEFAULT_SPARK_NUMBER(s_c)
{
    _LinesL_b.setPrimitiveType(sf::PrimitiveType::Lines);
    _LinesL_b.resize(255);
    _LinesR_b.setPrimitiveType(sf::PrimitiveType::Lines);
    _LinesR_b.resize(255);
    _LinesL_h.setPrimitiveType(sf::PrimitiveType::Lines);
    _LinesL_h.resize(255);
    _LinesR_h.setPrimitiveType(sf::PrimitiveType::Lines);
    _LinesR_h.resize(255);
    _Sparks.setPrimitiveType(sf::PrimitiveType::Points);
    _Sparks.resize(DEFAULT_SPARK_NUMBER);
    _canvas = canvas;

    _sparkTab = new std::pair <int,double>[_Sparks.getVertexCount()];

    int e_(1);//bands
    for(int i=1; i<128; i++)
    {
        _LinesR_b[i].color = sf::Color(e_, 127+e_, 255-e_);
        _LinesR_h[i].color = sf::Color(e_, 127+e_, 255-e_);
        _LinesL_b[i].color = sf::Color(e_, 127+e_, 255-e_);
        _LinesL_h[i].color = sf::Color(e_, 127+e_, 255-e_);
        ++e_;
    }

    _velocity = DEFAULT_VELOCITY;
    _verticalOffset = 50;
    for(int i=0; i<_Sparks.getVertexCount(); i++)
    {
        _Sparks[i].color = sf::Color(_g()%50+130, _g()%20+200, _g()%55+200);
        _Sparks[i].position = sf::Vector2f(_g()%800,_g()%600);
        _sparkTab[i] = std::make_pair(i,(double)(_velocity+_g()%30)) ;
    }

}

LineDisplayer::~LineDisplayer()
{
    //dtor
    delete _sparkTab;
}

void LineDisplayer::draw(float* d_, float avg,sf::Time t_e,sf::SoundSource::Status status)
{
    //_localBounds.width/2,_localBounds.height/2;
    if(status == sf::SoundSource::Status::Playing)
    {
        int e_(3);//bands
        if(d_[1] < 400)
        {
            for(int i=2; i<128; i++)
            {
                if(i%2 == 0)
                {
                    _LinesR_b[i].position = sf::Vector2f((400) + e_,(351));
                    _LinesR_h[i].position = sf::Vector2f((400) + e_,(249));
                    _LinesL_b[i].position = sf::Vector2f((400) - e_,(351));
                    _LinesL_h[i].position = sf::Vector2f((400) - e_,(249));
                }
                else
                {
                    _LinesR_b[i].position = sf::Vector2f((400) + e_,(350)+ d_[i]+avg/4);
                    _LinesR_h[i].position = sf::Vector2f((400) + e_,(250)- d_[i]-avg/4);
                    _LinesL_b[i].position = sf::Vector2f((400) - e_,(350)+ d_[i]+avg/4);
                    _LinesL_h[i].position = sf::Vector2f((400) - e_,(250)- d_[i]-avg/4);
                    e_ += 6;
                }
            }
        }
        updateSparks(avg,t_e);
    }

    _canvas->Draw(_Sparks);
    _canvas->Draw(_LinesL_b);
    _canvas->Draw(_LinesL_h);
    _canvas->Draw(_LinesR_b);
    _canvas->Draw(_LinesR_h);
}


void LineDisplayer::updateSparks(float avg, sf::Time e_t)
{
    bool change(false);

    if(avg < 150){
    for(int i=0; i<_Sparks.getVertexCount(); i++)
    {
        change = false;
        if(_Sparks[i].position.x > 800){
            _Sparks[i].position = sf::Vector2f(0,_Sparks[i].position.y + _g()%_verticalOffset*e_t.asSeconds());
            change = true;
        }
        if(_Sparks[i].position.y > 600){
            _Sparks[i].position = sf::Vector2f(_Sparks[i].position.x + (_sparkTab[i].second+avg*3)*e_t.asSeconds(),0);
            change = true;
        }
        if(_Sparks[i].position.y < 0){
            _Sparks[i].position = sf::Vector2f(_Sparks[i].position.x + (_sparkTab[i].second+avg*3)*e_t.asSeconds(),600);
            change = true;
        }
        if(!change)
            _Sparks[i].position = sf::Vector2f(_Sparks[i].position.x + (_sparkTab[i].second+avg*3)*e_t.asSeconds(),_Sparks[i].position.y + _g()%_verticalOffset*e_t.asSeconds());
    }
    }
}

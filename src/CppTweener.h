/*****************

 This port was based in a inital code from Jesus Gollonet, him port Penners easing equations to C/C++:

 http://www.jesusgollonet.com/blog/2007/09/24/penner-easing-cpp/
 http://robertpenner.com/easing/

 I¥m just make a better wrapper a litlle more OOP e put some callbacks like the original Tweener
 (http://code.google.com/p/tweener/)


 wesley.marques@gmail.com  - Wesley Ferreira Marques
 http://codevein.com


 **********************/

#ifndef _CPP_TWEEEN_
#define _CPP_TWEEEN_

#include <math.h>
#include <list>
#include <vector>
#include <iostream>


#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

namespace tween {



    class Easing {
	public:
		Easing() {

		}
		//pure virtual
		virtual float easeIn(float t,float b , float c, float d)=0;
		virtual float easeOut(float t,float b , float c, float d)=0;
		virtual float easeInOut(float t,float b , float c, float d)=0;

    };

    class Back : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Bounce : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

	class Circ : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Cubic : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Elastic : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Expo : public Easing{

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Quad : public Easing {

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };


    class Quart : public Easing {

	public:

		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Quint : public Easing {
        public :
		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Sine : public Easing {
        public :
		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };

    class Linear : public Easing {
        public :
		float easeNone(float t,float b , float c, float d);
		float easeIn(float t,float b , float c, float d);
		float easeOut(float t,float b , float c, float d);
		float easeInOut(float t,float b , float c, float d);
    };


    enum {
        LINEAR,
        SINE,
        QUINT,
        QUART,
        QUAD,
        EXPO,
        ELASTIC,
        CUBIC,
        CIRC,
        BOUNCE,
        BACK

    };

    enum {
        EASE_IN,
        EASE_OUT,
        EASE_IN_OUT
	};



    static Linear fLinear;
    static Sine fSine;
    static Quint fQuint;
    static Quart fQuart;
    static Quad  fQuad;
    static Expo fExpo;
    static Elastic fElastic;
    static Cubic fCubic;
    static Circ fCirc;
    static Bounce fBounce;
    static Back fBack;



	struct TweenerProperty {
		float *ptrValue;
		float finalValue;
		float initialValue;
	};
	class TweenerParam  {



	public:
		std::vector<TweenerProperty>  properties;
		float time;
		short transition;
		short equation;
		float delay;
		float timeCount;
		int total_properties;
		bool useMilliSeconds;
		bool started;

		TweenerParam() {
			useMilliSeconds = true;
			timeCount = 0;
			started = false;

		}
		~TweenerParam(){
			properties.clear();

		}
		TweenerParam(float ptime,short ptransition = EXPO, short pequation = EASE_OUT) {
			time = ptime;
			transition = ptransition;
			equation = pequation;
			useMilliSeconds = true;
			timeCount = 0;
			started = false;
		}

		void addProperty(float *valor, float valorFinal) {
			TweenerProperty prop = {valor, valorFinal, *valor};
			properties.push_back(prop);
			total_properties = properties.size();
		}

		void setUseMilliSeconds(bool use ){
			useMilliSeconds = use;
		}

		void cleanProperties(){
			properties.clear();
			std::cout<<"\n-Parameter removed";
		}

		bool operator==( const TweenerParam& p ) {
			bool equal = false;
			if ((time == p.time) && (transition == p.transition) && (equation == p.equation) ){
				equal = true;
			}
			if (equal) {
				for (unsigned int i =0 ; i < p.total_properties; i++ ) {
					if( properties[i].initialValue != p.properties[i].initialValue ||
					   properties[i].finalValue != p.properties[i].finalValue) {
						equal = false;
						break;
					}
				}
			}
			return equal;
		}

	};
	class TweenerListener {
	public:
		TweenerListener(){};
		~TweenerListener(){};
		virtual void onStart(TweenerParam& param) = 0;
		virtual void onStep(TweenerParam& param) = 0 ;
		virtual void onComplete(TweenerParam& param) = 0 ;
		bool operator==( const TweenerListener& l ) {
			return (this == &l) ;
		};
    };


	class Tweener {
        protected :
		enum {ON_START, ON_STEP, ON_COMPLETE};
		short currentFunction ;
		Easing *funcs[11];
		long lastTime;

		std::list<TweenerParam> tweens;
		std::list<TweenerParam>::iterator tweensIT;
		std::list<TweenerListener*> listeners;
		std::list<TweenerListener*>::iterator listenerIT;
		int total_tweens ;

		float runEquation(int transition,int equation, float t,float b , float c, float d) {

			float result;
			if (equation == EASE_IN) {
				result = funcs[transition]->easeIn(t,b,c,d);
			} else if (equation == EASE_OUT) {
				result = funcs[transition]->easeOut(t,b,c,d);
			} else if (equation == EASE_IN_OUT) {
				result = funcs[transition]->easeInOut(t,b,c,d);
			}

			return result;
		}

		void dispatchEvent(TweenerParam *param, short eventType) {

			for (unsigned int i = 0; i < listeners.size(); i++ ) {
				listenerIT = listeners.begin();
				TweenerListener *listener = *listenerIT;
				switch(eventType) {
					case ON_START:
						listener->onStart(*param);
						break;
					case ON_STEP:
						listener->onStep(*param);
						break;
					case ON_COMPLETE:
						listener->onComplete(*param);
						break;
					default:
						std::cout<<"Event not found!!";
						break;
				}


			}
		}

	public:
		Tweener() {
			this->funcs[LINEAR] = &fLinear;
			this->funcs[SINE]  = &fSine;
			this->funcs[QUINT] = &fQuint;
			this->funcs[QUART] = &fQuart;
			this->funcs[QUAD] = &fQuad;
			this->funcs[EXPO] = &fExpo;
			this->funcs[ELASTIC] = &fElastic;
			this->funcs[CUBIC] = &fCubic;
			this->funcs[CIRC] =  &fCirc;
			this->funcs[BOUNCE] =  &fBounce;
			this->funcs[BACK] =  &fBack;



		}




		void addTween(TweenerParam& param) {
			param.timeCount = 0;

			for (int i =0 ; i < param.total_properties; i++ ) {
				TweenerProperty prop = param.properties[i];
				param.properties[i].initialValue = *(prop.ptrValue);

			}
			//std::cout<<" \nParam: props"<< (param).total_properties  << " time" << (param).time;

			tweens.push_back(param);
			total_tweens = tweens.size();

		}

		void removeTween(TweenerParam  *param) {

			total_tweens = tweens.size();
			tweensIT = tweens.begin();
			for (int i=0; i <  total_tweens; i++,tweensIT++) {
				if ((*param) == (*tweensIT)) {
					(*tweensIT).cleanProperties();
					tweens.erase(tweensIT);
					std::cout<<"\n-Tween Removed";
					--total_tweens;
					break;
				}
			}

		}

		void addListener(TweenerListener *listener) {
			listeners.push_back(listener);
		}


		void removeListener(TweenerListener *listener) {
			for (listenerIT = listeners.begin(); listenerIT != listeners.end(); ++listenerIT ) {
			  if (listener == (*listenerIT) ) {
					std::cout<< "\n-Listener removed";
					listeners.erase(listenerIT);
					listenerIT = listeners.begin();
					break;
				}
			}
		}
		void setFunction(short funcEnum) {
			if (funcEnum > -1 && funcEnum <=11) {
				currentFunction = funcEnum;
			}
		};

		void step(long currentMillis) {

			total_tweens = tweens.size();
			int t = 0 ;
			int d = 0;
			int  dif = (currentMillis - lastTime);

			for (tweensIT = tweens.begin(); tweensIT != tweens.end(); ++tweensIT ) {

				if (!(*tweensIT).started) {
					dispatchEvent(&(*tweensIT), ON_START);
					(*tweensIT).started = true;
				}

				dispatchEvent(&(*tweensIT), ON_STEP);

				if ((*tweensIT).useMilliSeconds == true) {
					((*tweensIT).timeCount)+=dif;
					t = (*tweensIT).timeCount;
				} else {
					((*tweensIT).timeCount)++;
					t =(*tweensIT).timeCount;
				}

				d = (*tweensIT).time ;
				if ( t < d  && (*tweensIT).total_properties > 0 ) {
					if ((*tweensIT).timeCount < (*tweensIT).time) {
						for (unsigned int i =0 ; i < (*tweensIT).total_properties; i++ ) {
							TweenerProperty prop = (*tweensIT).properties[i];
							if (prop.ptrValue != NULL ) {

								float  res   = runEquation(
														   (*tweensIT).transition,
														   (*tweensIT).equation,
														   t,
														   prop.initialValue,
														   (prop.finalValue - prop.initialValue ),
														   d);

								*(prop.ptrValue) = res;
							}
						}
					}



				} else {
					dispatchEvent(&(*tweensIT), ON_COMPLETE);
					removeTween(&(*tweensIT));
					tweensIT = tweens.begin();

				}
			}
			lastTime = currentMillis;

		};


    };




}

#endif

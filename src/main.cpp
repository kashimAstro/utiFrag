#include "var.h"
#include "ofxAssimpModelLoader.h"
#include "ofxUI.h"

class xApp : public ofBaseApp{

	public:
		ofxAssimpModelLoader model;
		ofxUISuperCanvas *gui;
		ofImage texture,texture1,colorMap,normalMap;
		int   counter = 0;
		bool  stopnoise,stopanim = true;
		float speedanim,alpha=1.0;

                void prepare_gui(){
                        gui = new ofxUISuperCanvas("configure",OFX_UI_FONT_SMALL);
                        gui->addSpacer();
                        gui->addLabel("hide gui press (h)");
                        gui->addSlider("speed anime", 0,      100,   70);
                        gui->addSpacer();
                        gui->addButton("stop anime", false);
                        gui->addSpacer();
                        gui->autoSizeToFitWidgets();
                        ofAddListener(gui->newGUIEvent,this,&xApp::guiEvent);
                }

                void guiEvent(ofxUIEventArgs &e){
                        string name = e.getName();
                        int kind = e.getKind();
                        cout << "event-from: " << name << endl;
                        if(name == "speed anime"){
                                ofxUISlider *slider = e.getSlider();
                                speedanim=slider->getScaledValue();
                        }
                        if(name == "stop anime"){
                                ofxUIButton *button = (ofxUIButton *) e.widget;
                                if(button->getValue() == true){
					stopanim=!stopanim;
				}
			}
		}

		void setup() {
		        ofSetFrameRate(60);
		        ofSetVerticalSync(true);

			bAnimate = false;
			bAnimateMouse = false;
			animationPosition = 0;
			model.loadModel("model/model.dae");
			model.setPosition( ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0 );
			model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
			model.playAllAnimations();

			if(!bAnimate) {
			        model.setPausedForAllAnimations(true);
			}
		        model.enableNormals();
			w=ofGetScreenWidth();
			h=ofGetScreenHeight();

			normal.load( "shader/vert_norm.glsl",  "shader/frag_norm.glsl" );
			tex.load(    "shader/vert_tex.glsl",   "shader/frag_tex.glsl" );
			bump.load(   "shader/vert_bump.glsl",  "shader/frag_bump.glsl" );
                        toon.load(   "shader/vert_toon.glsl",  "shader/frag_toon.glsl" );
			kal.load(    "shader/vert_kal.glsl",   "shader/frag_kal.glsl" );


			ofDisableArbTex();
			texture.loadImage("texture1.jpg");
			texture1.loadImage("texture.jpg");
			colorMap.loadImage("color.jpg");
			normalMap.loadImage("normal.jpg");

			camera.setFarClip(100000);
			speedanim=70;
                        prepare_gui();
		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			model.update();
			if(stopanim){
		        	animationPosition = ofMap(counter,0,speedanim,0.0,1.0);
				counter++;
				if(counter>speedanim)
					counter=0;
				model.setPositionForAllAnimations(animationPosition);
			}
		}

		void draw() {
			ofBackgroundGradient( ofColor(210), ofColor(10), OF_GRADIENT_BAR);

			ofEnableDepthTest();
			camera.begin();
			camera.setScale(1,-1,1);
				drawModel();
			camera.end();
			ofDisableDepthTest();
		}

		void drawModel(){
			ofPushMatrix();
			normal.begin();
				  ofTranslate(-320,0,0);
				  model.drawFaces();
			normal.end();
			ofPopMatrix();

			ofPushMatrix();
			tex.begin();
			tex.setUniformTexture("tex",texture.getTextureReference(),0);
				  ofTranslate(-90,0,0);
				  model.drawFaces();
			tex.end();
			ofPopMatrix();

			ofPushMatrix();
			bump.begin();
			bump.setUniformTexture("colorMap",colorMap.getTextureReference(),0);
 			bump.setUniformTexture("normalMap",normalMap.getTextureReference(),1);
				  ofTranslate(150,0,0);
				  model.drawFaces();
			bump.end();
			ofPopMatrix();

			ofPushMatrix();
			toon.begin();
			toon.setUniform3f("lightDir",0.2,0.45,0.4);
				  ofTranslate(400,0,0);
				  model.drawFaces();
			toon.end();
			ofPopMatrix();

			ofPushMatrix();
			kal.begin();
			kal.setUniformTexture("tex",texture.getTextureReference(),0);
			kal.setUniform1f("time", ofGetElapsedTimef());
			kal.setUniform2f("resol",w,h);
				  ofTranslate(600,0,0);
				  model.drawFaces();
			kal.end();
			ofPopMatrix();

		}

		void keyPressed(int key) {
		        switch (key) {
				case 'h':
					gui->toggleVisible();
					break;
				case 'f':
					ofToggleFullscreen();
					break;
		                default:
		                        break;
		        }
		}

};

int main(){
       ofAppGLFWWindow window;
       ofSetupOpenGL(&window, 1024,768, OF_FULLSCREEN);
       ofRunApp( new xApp());
}

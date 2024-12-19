#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_step = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 25, 0.2, 0.002);
	} else 	{

		this->noise_step += 0.002;
	}

	float span = 1;
	ofColor color;

	for (int k = 0; k < 3; k++) {

		for (float x = ofGetWindowWidth() * -0.5 + 30; x < ofGetWindowWidth() * 0.5 - 30 - span; x += span) {

			for (float y = ofGetWindowHeight() * -0.5 + 30; y < ofGetWindowHeight() * 0.5 - 30 - span; y += span) {

				this->mesh.addVertex(glm::vec3(x, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
				this->mesh.addVertex(glm::vec3(x, y + span, 0));

				for (int i = this->mesh.getNumVertices() - 4; i < this->mesh.getNumVertices(); i++) {

					auto noise_value = ofMap(ofNoise(k * 0.5, this->mesh.getVertex(i).x * 0.001, this->mesh.getVertex(i).y * 0.001, glm::length(this->mesh.getVertex(i)) * 0.004 - this->noise_step), 0, 1, 0, 3);
					int int_noise_value = noise_value;
					float param = noise_value - int_noise_value;
					param = abs(param - 0.5);

					auto hue = (int)ofMap(noise_value, 0, 3, 128, 255 + 128) % 255;
					auto alpha = param < 0.2 ? ofMap(param, 0, 0.2, 255, 0) : 0;

					color.setHsb((int)ofMap(k, 0, 3, 128, 255 + 128) % 255, 200, 200, alpha);
					this->mesh.addColor(color);
				}

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	this->mesh.draw();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	float phi_deg_step = 10;
	float theta_deg_step = 6;

	for (int x = -600; x <= 600; x += 600) {

		for (int z = -600; z <= 600; z += 600) {

			for (float radius = 150; radius <= 250; radius += 100) {

				for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

					for (float theta_deg = 0; theta_deg <= 180; theta_deg += theta_deg_step) {

						auto noise_value = ofNoise(glm::vec3(
							x + radius * sin(theta_deg * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD) * 0.003,
							radius * sin(theta_deg * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD) * 0.003,
							z + radius * cos(theta_deg * DEG_TO_RAD) * 0.003 +
							ofGetFrameNum() * 0.03));

						if (noise_value > 0.55) {

							auto index = this->face.getNumVertices();
							vector<glm::vec3> vertices;

							vertices.push_back(glm::vec3(
								x + radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
								radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
								z + radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
							vertices.push_back(glm::vec3(
								x + radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
								radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
								z + radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
							vertices.push_back(glm::vec3(
								x + radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
								radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
								z + radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
							vertices.push_back(glm::vec3(
								x + radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
								radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
								z + radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

							this->face.addVertices(vertices);
							this->frame.addVertices(vertices);

							this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
							this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

							this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
							this->frame.addIndex(index + 0); this->frame.addIndex(index + 2);
							this->frame.addIndex(index + 3); this->frame.addIndex(index + 1);
							this->frame.addIndex(index + 3); this->frame.addIndex(index + 2);
						}
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	ofSetColor(239, 71, 111);
	this->face.draw();

	ofSetColor(239);
	this->frame.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
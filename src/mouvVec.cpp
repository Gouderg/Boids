#include "../include/mouvVec.h"

MouvVec::MouvVec(const double x, const double y, const double z) {
	this->x = x;
	this->y = y;
	this->z = z;
}


void MouvVec::add(MouvVec v) {
	this->x += v.getX();
	this->y += v.getY();
	this->z += v.getZ();
}

void MouvVec::sub(MouvVec v) {
	this->x -= v.getX();
	this->y -= v.getY();
	this->z -= v.getZ();
}

void MouvVec::div(MouvVec v) {
	this->x /= v.getX();
	this->y /= v.getY();
	this->z /= v.getZ();	
}

void MouvVec::mul(MouvVec v) {
	this->x *= v.getX();
	this->y *= v.getY();
	this->z *= v.getZ();	
}

void MouvVec::add(double n) {
	this->x += n;
	this->y += n;
	this->z += n;
}

void MouvVec::sub(double n) {
	this->x -= n;
	this->y -= n;
	this->z -= n;
}

void MouvVec::div(double n) {
	this->x /= n;
	this->y /= n;
	this->z /= n;	
}

void MouvVec::mul(double n) {
	this->x *= n;
	this->y *= n;
	this->z *= n;	
}

MouvVec MouvVec::add(MouvVec v1, MouvVec v2) {
    MouvVec v;
    
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    
    return v;
}

MouvVec MouvVec::sub(MouvVec v1, MouvVec v2) {
    MouvVec v;
    
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    
    return v;
}

MouvVec MouvVec::div(MouvVec v1, MouvVec v2) {
    MouvVec v;
    
    v.x = v1.x / v2.x;
    v.y = v1.y / v2.y;
    v.z = v1.z / v2.z;
    
    return v;
}

MouvVec MouvVec::mul(MouvVec v1, MouvVec v2) {
    MouvVec v;
    
    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    v.z = v1.z * v2.z;
    
    return v;
}



double MouvVec::magnitude() {
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
	// return sqrt(pow(this->x,2) + pow(this->y, 2) + pow(this->z, 2));

}

double MouvVec::dist(MouvVec v1, MouvVec v2) {
	return sqrt(pow(v1.getX() - v2.getX(),2) + pow(v1.getY() - v2.getY(),2));
	// return sqrt(pow(v1.getX() - v2.getX(),2) + pow(v1.getY() - v2.getY(),2) +  pow(v1.getZ() - v2.getZ(),2)); 
}

void MouvVec::normalize() {
	double mag = this->magnitude();

	if (mag > 0) {
		this->div(mag);
	}
}

double MouvVec::headings() {
	return atan2(this->y, this->x) * 180/M_PI;
}

void MouvVec::setMag(double max) {
	this->normalize();
	this->mul(max);
}

double MouvVec::dotProduct(MouvVec v1, MouvVec v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

double MouvVec::angleBetween(MouvVec v1, MouvVec v2) {
    return acos(dotProduct(v1, v2) / (v1.magnitude() * v2.magnitude())) * 180/M_PI;
}

void MouvVec::limit(double max) {
    if (this->magnitude() > max) {
        this->normalize();
        this->mul(max);
    }
}

MouvVec MouvVec::rotate2D(MouvVec v1, double theta) {
    // Convert degrees to radians.
    theta = theta * M_PI / 180.0;
    
    MouvVec v;

    v.x = v1.x * cos(theta) + v1.y * sin(theta);
    v.y = v1.x * (-sin(theta)) + v1.y * cos(theta);
	v.z = 0;
    
    return v;
}

double MouvVec::angleWith(MouvVec ref_pos, MouvVec target, double theta) {

    MouvVec v;

    // Change the referentiel.
    v = sub(target, ref_pos);

    // Rotate the MouvVec.
    v = rotate2D(v, theta);

    return angleBetween(v, MouvVec(1, 0, 0));
}
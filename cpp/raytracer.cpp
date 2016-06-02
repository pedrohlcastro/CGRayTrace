#include "raytracer.h"
#include "vector.h"
#include <limits>

#include <iostream>
using namespace std;


// MÉTODO que gera um "raio inicial" (ou primário): aquele que parte do olho (câmera) e passa pelo pixel (i,j)
Ray RayTracer::generateInitialRay(Camera& camera, int row, int column, const int height, const int width) {
	Vector3 gridPointInCameraSpace = Vector3(column - width/2.0f, row - height/2.0f, -1);
	Ray ray;
	ray.p0 = camera.eye;
	ray.v = Vector3(gridPointInCameraSpace.diff(ray.p0));
	ray.v.normalize();
	return ray;
}

Vector3 RayTracer::castRay(Scene& scene, Ray& ray) {
	// Para todos os objetos da cena, verifica se o raio o acerta e pega aquele
	// que foi atingido primeiro (menor "t")
	double minimumT = numeric_limits<double>::max();
	Vector3 intersectionNormal;
	Object* closestObjectHit = NULL;
	for (int c = 0; c < scene.numObjs; c++) {
		Object* currentObject = &(scene.objects[c]);
		if (currentObject->intersectsWith(ray)) {
			if (ray.intersectionT < minimumT) {
				minimumT = ray.intersectionT;
				intersectionNormal = Vector3(ray.intersectionNormal);
				closestObjectHit = currentObject;
			}
		}
	}


	// Verifica se um objeto foi atingido. Se tiver sido, colore o pixel
	if (closestObjectHit != NULL) {
		// material e pigmento deste objeto
		Material* material= closestObjectHit->material;
		Pygment* pygment = closestObjectHit->pygment;

		// retorna simplesmente a cor do pigmento (da textura, digamos)
		return pygment->color1;
	}

	// nada foi atingido. Retorna uma cor padrão (de fundo)
	return Vector3(0, 0, 1);
}


// MÉTODO que renderiza uma cena, gerando uma matriz de cores.
// Parâmetros:
//   1. Scene& scene: um objeto do tipo Scene contendo a descrição da cena (ver scene.h)
//   2. Vector3** pixels: uma matriz de cores (representadas em Vector3 - r,g,b) que vamos "colorir"
//   3. const int height: altura da imagem que estamos gerando (e.g., 600px)
//   4. const int width: largura da imagem que estamos gerando (e.g., 800px)
void RayTracer::renderScene(Scene& scene, Vector3** pixels, const int height, const int width) {

	// Para cada pixel, lança um raio
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// cria um raio primário
			Ray ray = generateInitialRay(scene.camera, i, j, height, width);

			// lança o raio e recebe a cor
			Vector3 color = this->castRay(scene, ray);

			// salva a cor na matriz de cores
			pixels[i][j] = color;
		}
	}
}

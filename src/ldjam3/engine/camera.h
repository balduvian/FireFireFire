
#pragma once

#include "transform.h"

#include "../Types.h"
#include "../math/Matrix4.h"

namespace FFF {
	class Camera {
	public:
		f32 width;
		f32 height;

		Transform transform;

		/// default initialization
		Camera();

		/// a pos up orthographic projection matrix
		/// for 2d games
		void setOrtho(f32, f32);

		/// sets the view based off the transform
		void update();

		/// use this in shaders to get a non moving projection
		float* getProjection();

		/// use this in shaders to get a projection that moves
		/// with the camera
		float* getProjview();

	private:
		Matrix4f projection;
		Matrix4f projview;
	};
}
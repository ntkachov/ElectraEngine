package com.fbrs.electraengine;

import android.view.MotionEvent;

public class Camera {
	
	public float[] rotateVec = {1,0,0};
	public float[] translateVec = {0,0,0};
	
	public static float[] screenSize = {0,0};

	float x, y, xr, yr;
	float yrot = 0, xrot = 0;
	float xpos = 0, ypos = 0, zpos = -3;
	
	public Camera(float[] screen)
	{
		screenSize = screen;
	}
	
	public boolean TouchControls(MotionEvent v)
	{
		int p0 = v.getPointerId(0);
		int p1 = -5;
		if(v.getPointerCount() > 1)
			p1 = v.getPointerId(1);				

		boolean rotate = setRotateVec(v.getX(p0), v.getY(p0));
		boolean translate = false;
		if(!rotate)
			translate = setTranslateVec(v.getX(p0), v.getY(p0));
		if(v.getPointerCount() > 1){
			if(!rotate && translate)
				setRotateVec(v.getX(p1), v.getY(p1));
			if(!translate && rotate)
				setTranslateVec(v.getX(p1), v.getY(p1));
		}
		return true;
	}
	
	private boolean setRotateVec(float x, float y){
		
		x = x / screenSize[0];
		y = y / screenSize[1];
		if(x > .5){
			x -= .75;
			y -= .5;
		}
		else
			return false;
		
		yrot += y * 5; 
		xrot += x * 5;
		yrot = yrot % 360;
		xrot = xrot % 360;
		yr = (float) ((yrot / 180f) * Math.PI);
		xr = (float) ((xrot / 180f) * Math.PI);	
		rotateVec[0] = (float) Math.cos(xr);
		rotateVec[2] = (float) Math.sin(xr);
		rotateVec[1] = -(float) Math.sin(yr);
		return true;
	}
	
	private boolean setTranslateVec(float x, float y){
		
		x = x / screenSize[0];
		y = y / screenSize[1];
		if(x < .5){
			x -= .25;
			y -= .5;
			y *= -1;
		}
		else{
			return false;
		}

		translateVec[0] += ((rotateVec[0] * y) - (rotateVec[2] * x)) / 10;
		translateVec[2] += ((rotateVec[2] * y) + (rotateVec[0] * x)) / 10;
		return true;
	}

}

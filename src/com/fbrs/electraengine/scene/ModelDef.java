package com.fbrs.electraengine.scene;

public class ModelDef {
	public float[] rotate = {0,0,0};
	public float[] translate = {0,0,0};
	public String modelName;
	
	public ModelDef(){
		modelName = "";
	}
	
	public ModelDef(String s){
		String[] split = s.split(":");
		modelName = split[0];
		s = split[1];
		split = split[2].split(",");
		for(int i = 0; i < split.length; i++)
			rotate[i] = Float.parseFloat(split[i]);
		split = s.split(",");
		for(int i = 0; i < split.length; i++)
			translate[i] = Float.parseFloat(split[i]);
	}
	
	public void reGen(String s){
		String[] split = s.split(":");
		modelName = split[0];
		s = split[1];
		split = split[2].split(",");
		for(int i = 0; i < split.length; i++)
			rotate[i] = Float.parseFloat(split[i]);
		split = s.split(",");
		for(int i = 0; i < split.length; i++)
			translate[i] = Float.parseFloat(split[i]);
	}
}

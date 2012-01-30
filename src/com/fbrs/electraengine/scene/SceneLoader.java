package com.fbrs.electraengine.scene;

import java.io.IOException;

import com.fbrs.electraengine.ElectraHelper;
import com.fbrs.electraengine.ModelLoader;

public class SceneLoader {
	
	public static void loadScen(String Scene) throws IOException{
		String s = ElectraHelper.loadAsset(Scene);
		String[] subs = s.split("\n");
		ModelDef model = new ModelDef();
		for(int i = 0; i < subs.length; i++){
			model.reGen(subs[i]);
			ModelLoader.LoadModel(model.modelName, model.rotate, model.translate);
		}
	}


}

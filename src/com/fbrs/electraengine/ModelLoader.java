package com.fbrs.electraengine;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Random;

import android.content.Context;

public class ModelLoader {

	public static void LoadModel(Context context, String fileName) throws IOException{
		BufferedReader reader = new BufferedReader(new InputStreamReader(new DataInputStream( context.getAssets().open(fileName))));
		String line = "";
		ArrayList<Float> vertics = new ArrayList<Float>();
		ArrayList<Integer> ind = new ArrayList<Integer>();
		ArrayList<Float> norms = new ArrayList<Float>();
		Random rand = new Random();
		while((line = reader.readLine()) != null)
		{
			String[] split = line.split(" ");
			if(split[0].equals("v")){
				for(int i = 1; i < split.length; i++)
					vertics.add(Float.parseFloat(split[i]));
			}
			if(split[0].equals("f"))
			{
				for(int i = 1; i < split.length; i++)
					ind.add(Integer.parseInt(split[i].split("/")[0]));
			}
			if(split[0].equals("vn"))
			{
				
			}
		}
		float[] verts = new float[ind.size() * 3];
		
		/*for(Float f : vertics){
			verts[i] = f.floatValue();
			i++;
		}
		*/
		int[] indices = new int[ind.size()];
		
		for(int i = 0; i < ind.size(); i++)
		{
			int vert = ind.get(i)-1;
			verts[i*3] = vertics.get(vert*3);
			verts[i*3 + 1] = vertics.get(vert*3 + 1);
			verts[i*3 + 2] = vertics.get(vert*3 + 2);
		}
		GL2JNILib.LoadModel(verts, verts.length, verts, indices.length);
	}

}

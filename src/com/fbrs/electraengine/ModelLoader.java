package com.fbrs.electraengine;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.nio.Buffer;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Random;

import org.apache.http.util.ByteArrayBuffer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class ModelLoader {
	
	public static final int PV = 3;

	public static void LoadModel(String fileName, float[] rot, float[] trans) throws IOException{
		BufferedReader reader = new BufferedReader(new InputStreamReader(new DataInputStream(ActivityEntry.a.getAssets().open(fileName+".obj"))));
		String line = "";
		ArrayList<Float> vertics = new ArrayList<Float>();
		ArrayList<Integer> ind = new ArrayList<Integer>();
		ArrayList<Integer> indN = new ArrayList<Integer>();
		ArrayList<Integer> indU = new ArrayList<Integer>();
		ArrayList<Float> norms = new ArrayList<Float>();
		ArrayList<Float> Uvs = new ArrayList<Float>();
		ArrayList<Integer> polys = new ArrayList<Integer>();
		int CurrentGroup = 0;
		
		while((line = reader.readLine()) != null)
		{
			String[] split = line.split(" ");
			if(split[0].equals("v")){
				for(int i = 1; i < split.length; i++)
					vertics.add(Float.parseFloat(split[i]));
			}
			if(split[0].equals("f"))
			{
				for(int i = 1; i < split.length; i++){
					ind.add(Integer.parseInt(split[i].split("/")[0]));
					indU.add(Integer.parseInt(split[i].split("/")[1]));
					indN.add(Integer.parseInt(split[i].split("/")[2]));
				}
				polys.add(CurrentGroup);
			}
			if(split[0].equals("vn"))
			{
				for(int i = 1; i < split.length; i++)
					norms.add(Float.parseFloat(split[i].split("/")[0]));
			}
			if(split[0].equals("vt"))
			{
				for(int i = 1; i < split.length; i++)
					Uvs.add(Float.parseFloat(split[i]));
			}
			if(split[0].equals("g"))
			{
				CurrentGroup++;
			}
			
		}
		float[] verts = new float[ind.size() * 3];
		float[] norm = new float[ind.size() * 3];
		float[] uvs = new float[ind.size() * 2];
		int[] polygroups = new int[ind.size()*1];
		for(int i = 0; i < ind.size(); i++)
		{
			int p = i * 3;
			int vert = ind.get(i)-1;
			verts[p] = vertics.get(vert*3);
			verts[p + 1] = vertics.get(vert*3 + 1);
			verts[p + 2] = vertics.get(vert*3 + 2);
			vert = indN.get(i)-1;
			norm[p] = norms.get(vert*3);
			norm[p + 1] = norms.get(vert*3 + 1);
			norm[p + 2] = norms.get(vert*3 + 2);
			vert = indU.get(i)-1;
			uvs[i*2] = Uvs.get(vert * 2);
			uvs[i*2 + 1] = Uvs.get(vert * 2 + 1);
			polygroups[i] = polys.get(vert);
		}
		
		 Bitmap bMap = BitmapFactory.decodeStream(ActivityEntry.a.getAssets().open(fileName+".png"));
		ByteBuffer buf = ByteBuffer.allocate(bMap.getWidth() * bMap.getHeight() * 4);
		bMap.copyPixelsToBuffer(buf);
		GL2JNILib.LoadModel(verts, norm, uvs, verts.length, polygroups, rot, trans, buf.array(),bMap.getWidth());
		bMap.recycle();
	}

}

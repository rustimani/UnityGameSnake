using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class MyGameObject : MonoBehaviour {

	public int ScoreNow; //Поле в котором записываются очки текущего уровня
	public string[] filename; //файлы assest\resourses
	public string[] dest; //промежуточные файлы для обновления scores
	public string sc;
	public string ss;

	// Use this for initialization
	void Start()
	{
		filename = new string[1];
		filename[0] = @"C:\\Users\Public\Documents\Unity Projects\3kk\Assets\Resources\ScoresEasy.txt";

			dest = new string[1];
		dest[0] = @"C:\\Users\Public\Documents\Unity Projects\3kk\scE.txt";

			try
		{
			using (StreamReader sr = new StreamReader(filename[0]))
			{
				sc = sr.ReadLine();
				sr.Close();
			}
			ss = sc;
		}
		catch (System.Exception e)
		{
			Debug.Log(e.Message);
		}

		if (File.Exists(dest[0])) File.Create(dest[0]);

	}

	public void Save()
	{
		sc = ScoreNow.ToString();
	}

	public void Refresh()
	{
		try
		{

			using (StreamWriter sw = new StreamWriter(dest[0]))
			{


				sw.WriteLine(sc);
				sw.Close();

			}

			if (File.Exists(filename[0])) File.Delete(filename[0]);
			File.Copy(dest[0], filename[0]);
			File.Delete(dest[0]);

		}
		catch (System.Exception e)
		{
			Debug.Log(e.Message);
		}


	}
	// Use this for initialization

	// Update is called once per frame
	void Update() {

	}
}

using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour {

	public int GameMode = 0;
	public GameObject Snakes;
	GameObject SnakeObj;
	float X = 0, Y = 0;
	public LevelBuilder m_LevelBuilder;
	public GameObject Food;
	public GameObject FoodAdventure;
	int TimeSpeed = 50;
	int Buff = 0;
	public string FileName;
	public MyGameObject My;
	public Camera Main;



	void OnGUI()
	{
		int posX = Screen.height / 2;
		int posY = Screen.width / 2;
		switch (GameMode)
		{
		case 0:
			if (GUI.Button(new Rect(new Vector2(posX + 100, posY - 250), new Vector2(200, 30)), "ScoreMode"))
			{
				m_LevelBuilder.m_CurrentLevel = 3;
				m_LevelBuilder.Build();
				CreateSnake();
			}
			if (GUI.Button(new Rect(new Vector2(posX + 100, posY - 200), new Vector2(200, 30)), "StoryMode"))
			{
				GameEasy();


			}
			if (GUI.Button(new Rect(new Vector2(posX + 100, posY - 150), new Vector2(200, 30)), "Scores"))
			{
				DisplayScore();
			}
			break;
		case 1:
			try
			{
				Snake S = SnakeObj.GetComponent<Snake>();
				int Score = 0;
				if (S != null)
				{
					Score = S.SnakeScore;

				}
				GUI.Label(new Rect(new Vector2(100, 4), new Vector2(200, 30)), "Score" + Score);
			}
			catch (System.Exception e) {};
			break;

		case 2:
		{
			string s = null;
			using (StreamReader sr = new StreamReader(@"C:\\Users\Public\Documents\Unity Projects\3kk\Assets\Resources\ScoresEasy.txt"))
			{
				s = sr.ReadLine();
				sr.Close();
			}


			GUI.Label(new Rect(new Vector2(posX, posY - 300), new Vector2(200, 30)), "Last Score is " + s);
			break;
		}

		case 4:

			GUI.Label(new Rect(new Vector2(posX + 150, posY - 150), new Vector2(200, 30)), "U WIN THE GAME");

			break;
		}
	}

	void GameEasy()
	{
		m_LevelBuilder.m_CurrentLevel = 0;
		m_LevelBuilder.MaxCout = 2;
		SnakeObj = Instantiate(Snakes) as GameObject;
		SnakeObj.name = "player";
		GameMode = 3;
		ClearSpace();
		m_LevelBuilder.Build();
	}

	void DisplayScore()
	{
		GameMode = 2;
	}


	void CreateSnake()
	{
		SnakeObj = Instantiate(Snakes) as GameObject;
		SnakeObj.name = "player";
		GameMode = 1;
	}

	bool IsLvlComplite()
	{
		FoodAdventure[] ff = FindObjectsOfType<FoodAdventure>();
		if (ff.Length == 0) return true;
		else return false;
	}

	void AddFood()
	{
		Instantiate(Food);

	}

	void ClearSpace()
	{
		Death[] deaths = FindObjectsOfType<Death>();
		foreach(var Death in deaths)
		{
			DestroyObject(Death.gameObject);
		}
		Food[] ff = FindObjectsOfType<Food>();
		foreach(var Food in ff)
		{
			DestroyObject(Food.gameObject);
		}
	}


	// Use this for initialization
	void Start() {

	}

	// Update is called once per frame
	void Update() {

		if (Input.GetKey(KeyCode.Escape))
		{

			FoodAdventure[] ff = FindObjectsOfType<FoodAdventure>();
			foreach(var Food in ff)
			{
				DestroyObject(Food.gameObject);
			}
			if (GameMode == 1)
			{
				My.Refresh();
			}
			if (GameMode != 0)
			{

				GameMode = 0;
				Snake S = SnakeObj.GetComponent<Snake>();
				S.SnakeDeath();
			}

		}
		if (SnakeObj != null && (GameMode == 1 || GameMode == 3 || GameMode == 4))
		{
			if (GameMode == 1)
			{
				Snake S = SnakeObj.GetComponent<Snake>();
				My.ScoreNow = S.SnakeScore;

			}
			X = 0; Y = 0;
			if (Input.GetAxis("Horizontal") > 0) X = 1;
			if (Input.GetAxis("Horizontal") < 0) X = -1;
			if (Input.GetAxis("Vertical") > 0) Y = 1;
			if (Input.GetAxis("Vertical") < 0) Y = -1;
			if ((X != 0) || (Y != 0))
			{
				Snake S = SnakeObj.GetComponent<Snake>();
				if (X != 0) S.Directiion = new Vector2(X, 0);
				if (Y != 0) S.Directiion = new Vector2(0, Y);
			}


		}
		else if (GameMode != 2)
		{
			My.Refresh();
			FoodAdventure[] ff = FindObjectsOfType<FoodAdventure>();
			foreach(var Food in ff)
			{
				DestroyObject(Food.gameObject);
			}
			GameMode = 0;
			ClearSpace();
		}
		if (GameMode == 1)
		{

			Buff++;
			if (Buff == TimeSpeed)
			{
				AddFood(); Buff = 0;
			}
			My.Save();
		}
		if (GameMode == 3)
		{
			if (IsLvlComplite())
			{
				if (m_LevelBuilder.MaxCout > m_LevelBuilder.m_CurrentLevel)
				{
					m_LevelBuilder.m_CurrentLevel++;
					ClearSpace();
					m_LevelBuilder.Build();

				}
				else if (m_LevelBuilder.m_CurrentLevel == m_LevelBuilder.MaxCout)
				{
					ClearSpace();
					FoodAdventure[] ff = FindObjectsOfType<FoodAdventure>();
					foreach(var Food in ff)
					{
						DestroyObject(Food.gameObject);
					}
					GameMode = 4;

				}

			}
		}

	}


}

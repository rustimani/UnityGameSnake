using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Snake : MonoBehaviour {

	public int SnakeScore = 0;
	int TimeSpeed = 10;
	int Buff = 0;

	public GameObject Body;
	List<GameObject> SnakeBody = new List<GameObject>();
	public Vector2 Directiion;
	float MoveSpeed = 5.7f;


	public void AddTail()
	{
		Vector3 Position = transform.position;
		if (SnakeBody.Count > 0)
		{
			Position = SnakeBody[SnakeBody.Count - 1].transform.position;
		}
		//Position.y+=0.5f;
		GameObject Tail = Instantiate(Body, Position, Quaternion.identity) as GameObject;
		SnakeBody.Add(Tail);
	}

	void SnakeMove()
	{
		if (Directiion.x != 0 || Directiion.y != 0)
		{
			Rigidbody Component = GetComponent<Rigidbody>();
			Component.velocity = new Vector3(Directiion.x * MoveSpeed, Directiion.y * MoveSpeed, 0);
			if (SnakeBody.Count > 0)
			{
				SnakeBody[0].transform.position = transform.position;
				for (int i = SnakeBody.Count - 1; i > 0; i--)
				{
					SnakeBody[i].transform.position = SnakeBody[i - 1].transform.position;
				}
			}
		}
		int kx = 0; int maxy, miny, maxx, minx;
		int ky = 0;
		for (int i = 3; i < SnakeBody.Count - 1; i++)
		{
			if (SnakeBody[i].transform.position.y > SnakeBody[i - 1].transform.position.y)
			{
				maxy = i; miny = i - 1;
			}
			else
			{
				maxy = i - 1; miny = i;
			}
			if (SnakeBody[i].transform.position.x > SnakeBody[i - 1].transform.position.x)
			{
				maxx = i; minx = i - 1;
			}
			else
			{
				maxx = i - 1; minx = i;
			}
			if (this.transform.position.x > SnakeBody[i].transform.position.x - 0.25 && this.transform.position.x < SnakeBody[i].transform.position.x + 0.25) {
				kx++;
				if (kx == 2)
				{

					if (this.transform.position.y >= SnakeBody[miny].transform.position.y && this.transform.position.y <= SnakeBody[maxy].transform.position.y) SnakeDeath();
					kx = 1;
				}
			}
			if (this.transform.position.y > SnakeBody[i].transform.position.y - 0.25 && this.transform.position.y < SnakeBody[i].transform.position.y + 0.25) {
				ky++;
				if (ky == 2)
				{

					if (this.transform.position.x >= SnakeBody[minx].transform.position.x && this.transform.position.x <= SnakeBody[maxx].transform.position.x) SnakeDeath();
					ky = 1;
				}
			}
			if (this.transform.position == SnakeBody[i].transform.position) SnakeDeath();
		}


	}

	public void SnakeDeath()
	{
		Directiion = new Vector2(0, 0);
		foreach(GameObject i in SnakeBody) DestroyObject(i.gameObject);
		DestroyObject(this.gameObject);
	}


	// Use this for initialization
	void Start() {
		SnakeBody.Clear();
		for (int i = 0; i < 3; i++) AddTail();

	}

	// Update is called once per frame
	void Update() {

		Buff++;
		if (Buff > MoveSpeed)
		{
			Buff = 0;
			SnakeMove();
		}

	}
}

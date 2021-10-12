using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Food : MonoBehaviour {

	int TimeSpeed = 250;
	int Buff = 0;


	// Use this for initialization
	void Start() {
		float X = Random.Range(-16, 16);
		float Y = Random.Range(-7, 7);
		this.transform.position = new Vector3(X, Y, 0);
	}


	// Update is called once per frame
	void Update() {
		Buff++;
		if (Buff == TimeSpeed)
		{
			DestroyObject(this.gameObject);
		}
	}

	void OnCollisionEnter(Collision collision)
	{
		Snake S = collision.gameObject.GetComponent<Snake>();
		if (S != null)
		{
			S.AddTail();
			S.SnakeScore++;
			DestroyObject(this.gameObject);
		}

	}
}

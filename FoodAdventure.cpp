using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FoodAdventure : MonoBehaviour {

	// Use this for initialization
	void Start() {

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
	// Update is called once per frame
	void Update() {

	}
}

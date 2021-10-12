using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Death : MonoBehaviour {

	// Use this for initialization
	void Start() {

	}

	// Update is called once per frame
	void Update() {

	}
	void OnCollisionEnter(Collision collision)
	{
		Snake S = collision.gameObject.GetComponent<Snake>();
		if (S != null)
		{
			// S.AddTail();
			S.SnakeScore = 0;
			S.SnakeDeath();
		}

	}
}

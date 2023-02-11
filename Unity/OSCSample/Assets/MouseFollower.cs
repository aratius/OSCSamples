using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MouseFollower : MonoBehaviour
{

    void Update()
    {
        Vector2 mousePosition = Input.mousePosition;
        Vector3 p = transform.localPosition;
        p.x = ((mousePosition.x / Screen.width) - .5f) * Camera.main.orthographicSize * 2f * (16f/9f);
        p.y = ((mousePosition.y / Screen.height) - .5f) * Camera.main.orthographicSize * 2f;
        transform.localPosition = p;
    }
}

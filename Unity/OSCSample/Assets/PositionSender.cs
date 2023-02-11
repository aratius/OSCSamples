using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PositionSender : MonoBehaviour
{

    [SerializeField] OscSender m_Sender;

    void Update()
    {
        m_Sender.Send("/position/x", transform.localPosition.x / (Camera.main.orthographicSize * 2f * (16f / 9f)) + .5f);
        m_Sender.Send("/position/y", -transform.localPosition.y / (Camera.main.orthographicSize * 2f) + .5f);

    }

    void OnMouseDown()
    {
        m_Sender.Send("/mouse/isPressed", 1);
        GetComponent<Renderer>().material.color = Color.red;
    }

    void OnMouseUp()
    {
        m_Sender.Send("/mouse/isPressed", 0);
        GetComponent<Renderer>().material.color = Color.white;
    }

}

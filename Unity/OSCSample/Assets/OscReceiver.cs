using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using OscJack;

public class OscReceiver : MonoBehaviour
{

    public UnityEvent<string, OscDataHandle> onOsc = new UnityEvent<string, OscDataHandle>();

    [SerializeField] int m_Port = 12000;

    OscServer m_Server;

    void Awake()
    {
        m_Server = new OscServer(m_Port);
        m_Server.MessageDispatcher.AddCallback(
            "",
            (string address, OscDataHandle data) => onOsc.Invoke(address, data)
        );
    }

    // Update is called once per frame
    void Update()
    {

    }
}

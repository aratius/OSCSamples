using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using OscJack;
using Cysharp.Threading.Tasks;

public class Sphere : MonoBehaviour
{
    [SerializeField] OscReceiver m_Receiver;

    // Start is called before the first frame update
    void Start()
    {
        m_Receiver.onOsc.AddListener(OnOsc);
    }

    async void OnOsc(string address, OscDataHandle data)
    {

        // Debug.Log($"data cnt : {data.GetElementCount()}");  // 引数の個数

        if(address == "/position/x") {
            float xNormalized = data.GetElementAsFloat(0);
            await UniTask.WaitForFixedUpdate();  // UnityEngineのAPIにはメインスレッドからアクセスしないといけないため
            SetX((xNormalized - .5f) * Camera.main.orthographicSize * 2f *(16f/9f));
        } else if (address == "/position/y") {
            float yNormalized = data.GetElementAsFloat(0);
            await UniTask.WaitForFixedUpdate();  // UnityEngineのAPIにはメインスレッドからアクセスしないといけないため
            SetY(-(yNormalized - .5f) * Camera.main.orthographicSize * 2f);
        } else if (address == "/mouse/isPressed") {
            int isPressed = data.GetElementAsInt(0);
            await UniTask.WaitForFixedUpdate();  // UnityEngineのAPIにはメインスレッドからアクセスしないといけないため
            SetColor(isPressed == 1);
        }
    }

    void SetX(float x)
    {
        SetPosition(new Vector3(x, transform.localPosition.y, transform.localPosition.z));
    }

    void SetY(float y)
    {
        SetPosition(new Vector3(transform.localPosition.x, y, transform.localPosition.z));
    }

    void SetPosition(Vector3 p)
    {
        transform.localPosition = p;
    }

    void SetColor(bool isActive)
    {
        Debug.Log(isActive);
        GetComponent<Renderer>().material.color = isActive ? Color.red : Color.white;
    }
}

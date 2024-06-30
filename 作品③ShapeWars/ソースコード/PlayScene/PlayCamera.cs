using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.InputSystem;
using Cinemachine;

public class PlayCamera : MonoBehaviour
{
    //  ゲームパッド
    private Gamepad gamepad;
    //  VirtualCamera
    private CinemachineVirtualCamera virtualCamera;
    //  CinemachinePOV
    private CinemachinePOV cinemachinePOV;

    // Start is called before the first frame update
    public void Init()
    {
        virtualCamera = gameObject.GetComponent<CinemachineVirtualCamera>();

        cinemachinePOV = virtualCamera.GetCinemachineComponent<CinemachinePOV>();
    }

    // Update is called once per frame
    public void CamUpdate()
    {
        //  ゲームパッドを取得
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        cinemachinePOV.m_VerticalAxis.m_InputAxisValue = gamepad.rightStick.ReadValue().y;
        cinemachinePOV.m_HorizontalAxis.m_InputAxisValue = gamepad.rightStick.ReadValue().x;
    }
}

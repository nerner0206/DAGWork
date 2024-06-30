using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThroughFloor : MonoBehaviour
{
    //  すり抜け床のコンポーネント
    private PlatformEffector2D m_effector;
    //  コントローラー
    private PlayerControll m_controll;

    void Start()
    {
        m_effector = GetComponent<PlatformEffector2D>();
        m_controll = new PlayerControll();
        m_controll.Enable();
    }

    void Update()
    {
        //  左スティックの下を押している間だけ上から下へすり抜ける
        if (m_controll.Player.Climb.ReadValue<float>() < -0.3f)
        {
            m_effector.rotationalOffset = 180f;
        }
        else
        {
            m_effector.rotationalOffset = 0f;
        }
    }
}

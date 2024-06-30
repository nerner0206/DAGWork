using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

[RequireComponent(typeof(CinemachineVirtualCamera))]
[RequireComponent(typeof(BoxCollider2D))]
public class ChangeCamera : MonoBehaviour
{
    [SerializeField, Tooltip("変更後の優先度")]
    private int m_afterPriority;

    //  切り替え後のカメラ
    private CinemachineVirtualCamera m_virtualCamera;
    //  デフォルトの優先度
    private int m_defaultPriority;

    void Start()
    {
        m_virtualCamera   = this.GetComponent<CinemachineVirtualCamera>();
        m_defaultPriority = m_virtualCamera.Priority;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  プレイヤーが範囲内に来たら、カメラの優先度を変更
        if (collision.transform.CompareTag("Player"))
        {
            m_virtualCamera.Priority = m_afterPriority;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        //  プレイヤーが範囲内から出たら、カメラの優先度を変更
        if (collision.transform.CompareTag("Player"))
        {
            m_virtualCamera.Priority = m_defaultPriority;
        }
    }

}

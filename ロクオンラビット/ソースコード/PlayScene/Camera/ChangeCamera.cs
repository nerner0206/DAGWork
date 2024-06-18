using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Cinemachine;

[RequireComponent(typeof(CinemachineVirtualCamera))]
[RequireComponent(typeof(BoxCollider2D))]
public class ChangeCamera : MonoBehaviour
{
    [SerializeField, Tooltip("�ύX��̗D��x")]
    private int m_afterPriority;

    //  �؂�ւ���̃J����
    private CinemachineVirtualCamera m_virtualCamera;
    //  �f�t�H���g�̗D��x
    private int m_defaultPriority;

    void Start()
    {
        m_virtualCamera   = this.GetComponent<CinemachineVirtualCamera>();
        m_defaultPriority = m_virtualCamera.Priority;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  �v���C���[���͈͓��ɗ�����A�J�����̗D��x��ύX
        if (collision.transform.CompareTag("Player"))
        {
            m_virtualCamera.Priority = m_afterPriority;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        //  �v���C���[���͈͓�����o����A�J�����̗D��x��ύX
        if (collision.transform.CompareTag("Player"))
        {
            m_virtualCamera.Priority = m_defaultPriority;
        }
    }

}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MessageCollider : MonoBehaviour
{
    [SerializeField, TextArea, Tooltip("�\�����郁�b�Z�[�W")]
    private string m_message;

    private PlaySceneText m_playSceneText;

    private bool m_once = false;

    private void Start()
    {
        //  �V�[���ɂ���PlaySceneText�X�N���v�g���擾
        m_playSceneText = FindObjectOfType<PlaySceneText>();
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  1�x�̂ݎ��s
        if (m_once) return;

        //  �v���C���[���R���C�_�[�ɓ���������e�L�X�g��\������
        if (collision.transform.CompareTag("Player"))
        {
            m_playSceneText.TextStart(m_message);
            m_once = true;
        }
    }
}

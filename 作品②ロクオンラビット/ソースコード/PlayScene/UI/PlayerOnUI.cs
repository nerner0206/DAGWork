using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerOnUI : MonoBehaviour
{
    //  �\������
    public bool display = false;

    [SerializeField, Header("�\������")]
    private float m_displayTime = 1f;

    //  �^�C�}�[
    private float m_timer = 0;

    public void Start()
    {
        //  �\������
        m_timer = m_displayTime;

        //  �摜�R���|�[�l���g���擾
        Image image = gameObject.GetComponent<Image>();
        Color color = image.color;
        //  �����x��߂�
        color.a = 1f;
        image.color = color;
    }

    private void Update()
    {
        //  �\�����Ȃ�
        if (display) return;

        //  �\�����Ԃ����炷
        if (m_timer > 0f)
        {
            m_timer -= Time.deltaTime;
            return;
        }

        //  �摜�R���|�[�l���g���擾
        Image image = gameObject.GetComponent<Image>();
        Color color = image.color;
        if (image.color.a > 0f)
        {
            //  ���X�ɓ�����
            color.a -= Time.deltaTime;
            image.color = color;
        }
        else
        {
            //  ��\��
            gameObject.SetActive(false);

            Start();
        } 
    }
}

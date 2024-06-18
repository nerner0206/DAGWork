using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Tilemaps;

public class HideTiles : MonoBehaviour
{
    //  �^�C���}�b�v
    private Tilemap m_tilemap;
    //  �B��Ă��邩�̐^�U�l
    private bool m_isHide;
    //  �����x
    private float m_alpha;

    //  �X�^�[�g
    void Start()
    {
        //  �R���|�[�l���g�̎擾
        m_tilemap = this.GetComponent<Tilemap>();
        //  ��B�ꒆ
        m_isHide = false;
        //  �s����
        m_alpha = 1f;
    }

    void Update()
    {
        //  �B�ꒆ�Ȃ珙�X�ɓ����ɂ���
        if (m_isHide)
            m_alpha -= Time.deltaTime;
        //  ��B�ꒆ�Ȃ珙�X�ɕs�����ɂ���
        else
            m_alpha += Time.deltaTime;

        //  �����x�͈̔͂ɔ[�߂�
        m_alpha = Mathf.Clamp(m_alpha, 0f, 1f);

        //  �����x�̕ύX
        m_tilemap.color = new Color(255f, 255f, 255f, m_alpha);
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        //  �v���C���[�Ȃ瓧���ɂ���
        if (collision.transform.CompareTag("Player"))
        {
            m_isHide = true;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        //  �v���C���[�Ȃ�s�����ɂ���
        if (collision.transform.CompareTag("Player"))
        {
            m_isHide = false;
        }

    }
}

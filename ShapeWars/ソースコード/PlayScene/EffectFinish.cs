using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectFinish : MonoBehaviour
{
    // Start is called before the first frame update
    public void Start()
    {
        //  �������ꂽ��Đ�
        gameObject.GetComponent<ParticleSystem>().Play();
    }
    // Update is called once per frame
    void Update()
    {
        //�p�[�e�B�N�����I��������폜
        if (gameObject.GetComponent<ParticleSystem>().isStopped)Destroy(gameObject);
    }
}

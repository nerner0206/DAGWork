using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EffectFinish : MonoBehaviour
{
    // Start is called before the first frame update
    public void Start()
    {
        //  生成されたら再生
        gameObject.GetComponent<ParticleSystem>().Play();
    }
    // Update is called once per frame
    void Update()
    {
        //パーティクルが終了したら削除
        if (gameObject.GetComponent<ParticleSystem>().isStopped)Destroy(gameObject);
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TItleWeaponController : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //  位置や角度を調整する
        gameObject.transform.position = new Vector3(Random.Range(-10.0f, 10.0f), 12.0f, 0.0f);
        gameObject.transform.localEulerAngles = new Vector3(0.0f, 0.0f, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        //  落下させる
        gameObject.transform.position = gameObject.transform.position + new Vector3(0.0f, -5.0f * Time.deltaTime, 0.0f);
        //  回転させる
        gameObject.transform.Rotate(new Vector3(0.0f, 0.0f, 200.0f * Time.deltaTime));

        //  画面内なら処理しない
        if (gameObject.transform.position.y > -30.0f) return;

        //  画面外に移動したら削除する
        Destroy(gameObject);
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MiniMap : MonoBehaviour
{
    //  カメラのオブジェクト
    [SerializeField] private GameObject mainCam;
    //  プレイヤーのオブジェクト
    [SerializeField] private GameObject player;

    //  プレイヤーの１フレーム前の位置
    private Vector3 oldPlayerPos;

    //  メインカメラの１フレーム前の角度
    private Vector3 oldCameraRot;

    // Start is called before the first frame update
    void Start()
    {
        //  プレイヤーの位置を入れる
        oldPlayerPos = player.transform.position;

        //  カメラの角度を入れる
        oldCameraRot = mainCam.transform.localEulerAngles;
    }

    // Update is called once per frame
    void Update()
    {
        //  今の位置を格納
        Vector3 nowPlayerPos = player.transform.position;
        //  前フレームとの差分
        Vector3 pos = nowPlayerPos - oldPlayerPos;

        //  カメラの位置を移動させる
        gameObject.transform.position += pos;

        //  今のカメラの角度
        Vector3 nowCameraRot = mainCam.transform.localEulerAngles;
        //  前フレームとの差分
        Vector3 rot = nowCameraRot - oldCameraRot;

        //  回転
        gameObject.transform.localEulerAngles += new Vector3(0.0f, rot.y, 0.0f);

        //  最後に前の位置・角度を変更
        oldPlayerPos = nowPlayerPos;
        oldCameraRot = nowCameraRot;
    }
}

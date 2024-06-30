using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.InputSystem;
using UnityEngine.SceneManagement;

//  メイクシーンの状態
public enum MakeSceneState
{
    Make,
    Preview,
    Save,
    Quit
};

//  メイクの状態
public enum MState
{
    IconFree,
    AddShapeSelect,
    ShapeMove,
    Animation
};

public class CMakeManager : MonoBehaviour
{
    //  メイクシーンの状態
    public static MakeSceneState sceneState;
    //  メイクの状態
    public static MState makeState;
    //  ゲームパッド
    private Gamepad gamepad;

    //  判定する
    private bool isMake;
    //  セーブ番号
    private int saveNum;
    //  アニメーション番号
    private int animID;

    /// <summary>
    /// オブジェクト
    /// </summary>
    //  動かすIcon
    [SerializeField] private GameObject moveIcon;
    //  図形を追加するオブジェクト
    [SerializeField] private GameObject shapeManager;
    //  カメラ
    [SerializeField] private GameObject cam;
    //  図形選択リスト
    [SerializeField] private GameObject addShapeSelectList;
    //  ハンドル
    [SerializeField] private GameObject handle;
    //  プレイヤー
    [SerializeField] private GameObject player;
    [SerializeField] private GameObject hand;

    //  操作方法UI
    [SerializeField] private List<GameObject> operater;
    //  テキスト
    [SerializeField] private List<Text> shapeNumTexts;

    //  セーブUI 
    [SerializeField] private GameObject saveUI;
    //  アイコン
    [SerializeField] private GameObject moveIcon2;

    //  パラメーター
    [SerializeField] private GameObject paramater;
    //  アニメーション
    [SerializeField] private GameObject animator;

    /// <summary>
    /// アイコンと反応するオブジェクト
    /// </summary>
    //  図形のリストを表示
    [SerializeField] private GameObject addArrowBack;
    //  プレビューカメラ画像
    [SerializeField] private GameObject previewCamImage;
    //  アニメーションアイコン
    [SerializeField] private List<GameObject> animIcons;

    // Start is called before the first frame update
    private void Start()
    {
        //  メイク状態
        sceneState = MakeSceneState.Make;
        //  最初はフリー
        makeState = MState.IconFree;

        isMake = true;

        saveNum = 0;

        operater[0].SetActive(true);

        animID = 0;
    }
    // Update is called once per frame
    private void Update()
    {
        Debug.Log(animID);

        //  ゲームパッドを取得
        gamepad = Gamepad.current;
        if (gamepad == null) return;

        switch(sceneState)
        {
            case MakeSceneState.Make:
                //  メイク状態の更新処理
                MakeStateUpdate();
                //  プレビューのカメラをハンドル中心に回転させる
                gameObject.GetComponent<PreviewManager>().PreviewCamRot(handle.transform.position);
                //  yが押されたとき
                if (gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  セーブするかどうか
                    isSave();
                    return;
                }
                //  上を押したらプレビュー状態にする
                if (gamepad.dpad.up.wasPressedThisFrame)
                {
                    ChangePreview();
                    return;
                }
                break;
            case MakeSceneState.Preview:
                //  プレビューの更新処理
                gameObject.GetComponent<PreviewManager>().PreviewUpdate();
                //  yが押されたとき
                if (gamepad.buttonNorth.wasPressedThisFrame)
                {
                    //  セーブするかどうか
                    isSave();
                    return;
                }
                //  上・aボタンを押したらメイク状態にする
                if (gamepad.dpad.up.wasPressedThisFrame || gamepad.aButton.wasPressedThisFrame)
                {
                    ChangeMake();
                    return;
                }
                break;
            case MakeSceneState.Save:
                saveNum = moveIcon2.GetComponent<MoveIcon>().SelectData();
                //  決定
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  セーブデータ１にセーブする
                    shapeManager.GetComponent<AddShapeManager>().Save(saveNum, animID);
                    //  シーン遷移
                    SceneManager.LoadScene("SelectScene");
                }
                //  戻る
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    if (isMake)
                    {
                        sceneState = MakeSceneState.Make;
                        moveIcon.SetActive(true);
                    }
                    else sceneState = MakeSceneState.Preview;

                    //  開く
                    saveUI.GetComponent<DoMove>().DoTweenLocalMove(new Vector3(0.0f, 1280.0f, 0.0f));
                }
                    break;
            case MakeSceneState.Quit:
                break;
        }
    }
    //  メイク状態の更新
    private void MakeStateUpdate()
    {
        switch (makeState)
        {
            case MState.IconFree:
                //  カメラの回転
                cam.GetComponent<MakeCamera>().CamRot();
                //  アイコンの移動
                moveIcon.GetComponent<MoveIcon>().FreeMove();

                //  bが押されたとき
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  それぞれのUIで反応しているか
                    //  図形リストボタン
                    if (addArrowBack.GetComponent<UIHit>().hit) ChangeAddShapeSelect();
                    //  プレビューカメラ
                    else if (previewCamImage.GetComponent<UIHit>().hit) ChangePreview();
                    //  それ以外ならオブジェクトに対してレイを飛ばす
                    else
                    {
                        //  レイを飛ばしてオブジェクトがあったか
                        bool isObj = shapeManager.GetComponent<EditShapeManager>().FlyingRay(
                            moveIcon.transform.position,
                            cam.transform.position);

                        //  オブジェクトが無ければ処理しない
                        if (!isObj) return;

                        //  編集モード
                        makeState = MState.ShapeMove;
                        //  Iconを非表示にする
                        moveIcon.SetActive(false);
                        //  操作方法を変える
                        operater[2].SetActive(true);
                        operater[0].SetActive(false);
                        operater[1].SetActive(false);
                    }
                    return;
                }
                //  xが押されたとき
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  追加するオブジェクトを選ぶ
                    ChangeAddShapeSelect();
                    return;
                }
                //  アニメーション
                if(gamepad.dpad.down.wasPressedThisFrame)
                {
                    //  アニメーション状態にする
                    makeState = MState.Animation;
                    //  UIの表示
                    paramater.SetActive(false);
                    animator.SetActive(true);
                    //  プレイヤーの非表示
                    player.SetActive(true);
                    //  子オブジェクトにする
                    handle.transform.parent = hand.transform;
                    //  武器の位置・角度調整
                    handle.transform.localPosition = new Vector3(-0.844f, 0.145f, -0.402f);
                    handle.transform.localEulerAngles = new Vector3(0.436f, -30.855f, 89.739f);
                    return;
                }
                //  aが押されたとき
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    //  終了するかどうか
                    isQuit();
                    return;
                }

                break;
            case MState.AddShapeSelect:
                //  カメラの回転
                cam.GetComponent<MakeCamera>().CamRot();
                //  アイコンの移動
                int num = moveIcon.GetComponent<MoveIcon>().ShapeSelectMove();

                //  bボタンが押されたとき
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  生成する
                    GameObject createObj = shapeManager.GetComponent<AddShapeManager>().AddShape(num);
                    //  増やす
                    int sub = int.Parse(shapeNumTexts[num].text);
                    shapeNumTexts[num].text = (sub + 1).ToString();
                    //  選択オブジェクトを渡す
                    shapeManager.GetComponent<EditShapeManager>().SetSelectObject(createObj);
                    //  リストを閉じてオブジェクト移動状態にする
                    CloseList(MState.ShapeMove);
                    //  Iconを非表示にする
                    moveIcon.SetActive(false);
                    //  操作方法を変える
                    operater[2].SetActive(true);
                    operater[0].SetActive(false);
                    operater[1].SetActive(false);
                    return;
                }
                //  xかbが押されたとき
                if (gamepad.buttonWest.wasPressedThisFrame || gamepad.aButton.wasPressedThisFrame)
                {
                    //  リストを閉じてフリー状態にする
                    CloseList(MState.IconFree);
                    //  アイコンの位置を真ん中にする
                    moveIcon.transform.localPosition = Vector3.zero;
                    //  操作方法を変える
                    operater[0].SetActive(true);
                    operater[2].SetActive(false);
                    operater[1].SetActive(false);
                    return;
                }

                break;
            case MState.ShapeMove:
                //  カメラの回転
                cam.GetComponent<MakeCamera>().CamRot();
                //  編集する
                shapeManager.GetComponent<EditShapeManager>().EditShapeUpdate();
                //  メーターの更新
                shapeManager.GetComponent<ParamaterManager>().MaterUpdate();

                //  xが押されたとき(追加でリストを開く)
                if (gamepad.buttonWest.wasPressedThisFrame)
                {
                    //  オブジェクトを解除する
                    shapeManager.GetComponent<EditShapeManager>().ResetSelectObject();
                    //  Iconを表示にする
                    moveIcon.SetActive(true);
                    //  追加するオブジェクトを選ぶ
                    ChangeAddShapeSelect();
                    return;
                }
                //  bが押されたとき(完了)
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  オブジェクトを解除する
                    shapeManager.GetComponent<EditShapeManager>().ResetSelectObject();
                    //  Iconを表示にする
                    moveIcon.SetActive(true);
                    //  アイコンの位置を調整
                    IconOnObject();
                    //  アイコンフリーにする
                    makeState = MState.IconFree;
                    //  操作方法を変える
                    operater[0].SetActive(true);
                    operater[1].SetActive(false);
                    operater[2].SetActive(false);
                    return;
                }
                //  aが押されたとき（削除）
                if (gamepad.buttonSouth.wasPressedThisFrame)
                {
                    //  メーターの更新
                    shapeManager.GetComponent<ParamaterManager>().DeleteMater();
                    //  オブジェクトを削除する
                    shapeManager.GetComponent<EditShapeManager>().DeleteShape();
                    //  Iconを表示にする
                    moveIcon.SetActive(true);
                    //  アイコンの位置を調整
                    IconOnObject();
                    //  アイコンフリーにする
                    makeState = MState.IconFree;
                    //  操作方法を変える
                    operater[0].SetActive(true);
                    operater[1].SetActive(false);
                    operater[2].SetActive(false);
                    return;
                }

                break;
            case MState.Animation:
                //  カメラの回転
                cam.GetComponent<MakeCamera>().CamRot();
                //  アイコンの移動
                moveIcon.GetComponent<MoveIcon>().FreeMove();

                //  bが押されたとき
                if (gamepad.buttonEast.wasPressedThisFrame)
                {
                    //  それぞれのUIで反応しているか
                    //  図形リストボタン
                    if (addArrowBack.GetComponent<UIHit>().hit)
                    {
                        //  UIの表示
                        paramater.SetActive(true);
                        animator.SetActive(false);
                        //  子オブジェクトを外す
                        handle.transform.parent = null;
                        //  初期化
                        handle.transform.position = Vector3.zero;
                        handle.transform.eulerAngles = Vector3.zero;
                        //  プレイヤーの非表示
                        player.SetActive(false);
                        //  変更
                        ChangeAddShapeSelect();
                    }
                    //  プレビューカメラ
                    else if (previewCamImage.GetComponent<UIHit>().hit) ChangePreview();
                    //  アニメーションアイコン
                    else if (animIcons[0].GetComponent<UIHit>().hit) ChangeAnim(0);
                    else if (animIcons[1].GetComponent<UIHit>().hit) ChangeAnim(1);
                    else if (animIcons[2].GetComponent<UIHit>().hit) ChangeAnim(2);
                    else if (animIcons[3].GetComponent<UIHit>().hit) ChangeAnim(3);
                    else if (animIcons[4].GetComponent<UIHit>().hit) ChangeAnim(4);
                    else if (animIcons[5].GetComponent<UIHit>().hit) ChangeAnim(5);
                    //  それ以外ならオブジェクトに対してレイを飛ばす
                    else
                    {
                        //  レイを飛ばしてオブジェクトがあったか
                        bool isObj = shapeManager.GetComponent<EditShapeManager>().FlyingRay(
                            moveIcon.transform.position,
                            cam.transform.position);

                        //  オブジェクトが無ければ処理しない
                        if (!isObj) return;

                        //  UIの表示
                        paramater.SetActive(true);
                        animator.SetActive(false);
                        //  子オブジェクトを外す
                        handle.transform.parent = null;
                        //  初期化
                        handle.transform.position = Vector3.zero;
                        handle.transform.eulerAngles = Vector3.zero;
                        //  プレイヤーの非表示
                        player.SetActive(false);
                        //  編集モード
                        makeState = MState.ShapeMove;
                        //  Iconを非表示にする
                        moveIcon.SetActive(false);
                        //  操作方法を変える
                        operater[2].SetActive(true);
                        operater[0].SetActive(false);
                        operater[1].SetActive(false);
                    }
                    return;
                }
                //  アニメーション
                if (gamepad.dpad.down.wasPressedThisFrame)
                {
                    //  アニメーション状態にする
                    makeState = MState.IconFree;
                    //  UIの表示
                    paramater.SetActive(true);
                    animator.SetActive(false);
                    //  子オブジェクトを外す
                    handle.transform.parent = null;
                    //  初期化
                    handle.transform.position = Vector3.zero;
                    handle.transform.eulerAngles = Vector3.zero;
                    //  プレイヤーの非表示
                    player.SetActive(false);
                    return;
                }
                break;
        }
    }
    private void ChangeAnim(int num)
    {
        animID = num;
        gameObject.GetComponent<AnimatorManager>().SetAnimClip(animID);
        player.GetComponent<Animator>().SetTrigger("Attack");
    }
    //  アイコンの位置をオブジェクトの位置に出す
    public void IconOnObject()
    {
        //  位置をもらう
        Vector3 objScreenPos = shapeManager.GetComponent<EditShapeManager>().GetObjScreenPos();
        //  位置をアイコンに渡す
        moveIcon.transform.position = new Vector3(objScreenPos.x, objScreenPos.y, 0.0f);
    }
    //  切り替え
    private void ChangeAddShapeSelect()
    {
        //  状態を切り替える
        makeState = MState.AddShapeSelect;
        //  操作方法を変える
        operater[1].SetActive(true);
        operater[0].SetActive(false);
        operater[2].SetActive(false);
        //  リストを出す
        addShapeSelectList.GetComponent<DoMove>().DoTweenWorldMove(new Vector3(
            150.0f,
            addShapeSelectList.transform.position.y, 
            addShapeSelectList.transform.position.z));
    }
    //  リストを閉じる
    private void CloseList(MState makeSceneState)
    {
        //  状態を切り替える
        makeState = makeSceneState;
        //  リストをしまう
        addShapeSelectList.GetComponent<DoMove>().DoTweenWorldMove(new Vector3(
            -140.0f,
            addShapeSelectList.transform.position.y,
            addShapeSelectList.transform.position.z));
    }
    //  やめる
    private void isQuit()
    {
        sceneState = MakeSceneState.Quit;
    }
    //  セーブする
    private void isSave()
    {
        //  セーブ状態にする
        sceneState = MakeSceneState.Save;
        //  アイコンを非表示
        moveIcon.SetActive(false);
        //  開く
        saveUI.GetComponent<DoMove>().DoTweenLocalMove(Vector3.zero);
    }
    //  プレイヤーをONにする
    private void OnPlayer()
    {
        //  プレイヤーを表示
        player.SetActive(true);
    }
    //  プレイヤーをOFFにする
    private void OffPlayer()
    {
        //  プレイヤーを非表示
        player.SetActive(false);
    }
    //  プレビュー状態にする
    private void ChangePreview()
    {
        //  プレビュー状態にする
        sceneState = MakeSceneState.Preview;
        //  アイコンを非表示
        moveIcon.SetActive(false);
        //  プレビュー判定
        isMake = false;
        //  変形
        gameObject.transform.GetComponent<PreviewManager>().MoveAfter();
    }
    //  メイク状態にする
    private void ChangeMake()
    {
        //  メイク状態にする
        sceneState = MakeSceneState.Make;
        //  アイコンを表示
        moveIcon.SetActive(true);
        //  メイク判定
        isMake = true;
        //  変形
        gameObject.transform.GetComponent<PreviewManager>().MoveBefore();
    }
}
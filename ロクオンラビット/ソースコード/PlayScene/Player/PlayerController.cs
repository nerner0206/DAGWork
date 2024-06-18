using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using NaughtyAttributes;
using Unity.Burst;
using DG.Tweening;
using UnityEngine.InputSystem;

[RequireComponent(typeof(Rigidbody2D))]

public class PlayerController : MonoBehaviour
{
    //  プレイヤーの状態
    private enum PlayerState
    {
        Move,           //  移動状態（移動）
        Play,           //  再生状態
        Rec,            //  録音状態
        Attack          //  攻撃状態
    };

    [Header("運動性能")]
    [SerializeField, Tooltip("歩きの加速度")]
    private float m_walkingAcceleration;
    [SerializeField, Tooltip("ジャンプの高さ")]
    private float m_jumpHeight;
    [SerializeField, Tooltip("歩きの最高速度")]
    private float m_walkMaxSpeed;
    [SerializeField, Tooltip("地面の減速が適用されるまでの時間")]
    private float m_landingTime;
    [SerializeField, Tooltip("地面の摩擦"), Range(0f, 1f)]
    private float m_friction;

    [Header("接地判定用のRayの設定")]
    [SerializeField, Tooltip("Rayの半径")]
    private float m_checkRadius;
    [SerializeField, Tooltip("Rayの距離")]
    private float m_checkDistance;

    [Header("ギミックとの当たり判定")]
    [SerializeField, Tooltip("Rayの半径")]
    private float m_SECheckRadius;
    [SerializeField, Tooltip("はしごを上る速度")]
    private float m_climbSpeed;

    [SerializeField, Header("攻撃"), Tooltip("攻撃時のレイの位置")]
    private Transform m_attackPoint;
    [SerializeField, Tooltip("Rayの半径")]
    private float m_attackRayRad = 0.1f;

    [SerializeField, Tooltip("物理挙動コンポーネント")]
    private Rigidbody2D m_rb;

    [SerializeField, Tooltip("スプライトオブジェクト")]
    private GameObject m_playerSprite;

    [SerializeField, Tooltip("歩くエフェクト")]
    private ParticleSystem m_walkEffect;
    [SerializeField, Tooltip("着地エフェクト")]
    private ParticleSystem m_onGroundEffect;

    [SerializeField, Tooltip("AudioSource")]
    private AudioSource m_audioSource;
    
    [SerializeField, Tooltip("ジャンプ・着地音")]
    private AudioClip m_jumpAudio;

    /// <summary>
    /// UI
    /// </summary>
    [SerializeField, Header("録音可能アイコン")]
    private GameObject m_recordingUI;
    [SerializeField, Header("録音不可能アイコン")]
    private GameObject m_nonRecordingUI;

    //  アニメーションコンポーネント
    private Animator m_animator;
    //  アニメーションスクリプト
    private PlayerAnim m_playerAnim;
    //  コントローラー
    private PlayerControll m_controll;
    //  プレイヤー音管理スクリプト
    private PlayerHaveSound m_haveSound;

    //  プレイヤーの状態
    private PlayerState m_state;

    //  現在のジャンプ回数
    private int m_currentJumpNum;
    //  向いている方向　1 : 右　-1 : 左
    private int m_direction;
    //  前フレームの着地判定
    private bool m_beforeGround;
    //  着地中の時間を計る
    private float m_landingTimer;
    //  はしごの前にいる
    private bool m_onLadder;
    //  はしごを上っている
    private bool m_climbing;
    //  重力の大きさの保持
    private float m_gravity; 
    //  移動の入力量
    private float m_move;
    //  登りの入力量
    private float m_climb;
    //  地上判定
    private bool m_onGround;

    //  コントローラーの振動力
    private float m_magPower;

    //  ジャンプ中判定
    private bool m_jumping = false;
    //  死亡判定
    private bool m_isDead = false;
    //  振動
    private bool m_mag;

    //  クリア演出用変数
    private Vector3 m_defPos;
    private Vector3 m_goalPos;
    //  クリア用タイマー
    private float m_clearTimer;

    //  設定クラス
    private OptionUI m_option;

    public void Init(PlayerControll inputActions)
    {
        m_controll       = inputActions;
        m_animator       = m_playerSprite.GetComponent<Animator>();
        m_playerAnim     = m_playerSprite.GetComponent<PlayerAnim>();
        m_beforeGround   = false;
        m_landingTimer   = 0f;
        m_haveSound      = gameObject.GetComponent<PlayerHaveSound>();
        m_haveSound.Init();
        m_climbing       = false;
        m_gravity        = m_rb.gravityScale;
        m_direction      = 1;
        m_onGround = false;

        m_option = OptionUI.GetInstance.GetComponent<OptionUI>();

        m_jumping = false;

        m_mag = false;

        m_magPower = 0.1f;

        m_playerAnim.GetSetIsStart    = false;
        m_isDead                      = false;
        //  アニメーションの再生
        m_animator.SetBool("IsDead", m_isDead);
        m_playerAnim.GetSetIsGameOver = false;

        //  初期状態:移動
        m_state = PlayerState.Move;

        m_move = 0.0f;
        m_climb = 0.0f;

        //  初期化
        m_playerAnim.GetSetIsStart = false;
        m_playerAnim.GetSetIsGameOver = false;
        m_jumping = false;
        m_playerAnim.GetSetAttack = false;

        //  エフェクト類
        m_walkEffect.transform.localEulerAngles = new Vector3(-90.0f, 0.0f, 0.0f);
    }
    
    void Update()
    {
        Gamepad gamepad = Gamepad.current;
        //  死んでたら/プレイ中では無いなら処理しない/Optionを開いている
        if (m_isDead || PlaySceneManager.m_sceneState != PlaySceneState.Playing || OptionUI.m_isOption)
        {
            
            if (gamepad != null) gamepad.SetMotorSpeeds(0.0f, 0.0f);
            m_rb.velocity = Vector3.zero;
            m_audioSource.Stop();
            return;
        }

        //  振動する
        if (m_mag) { if (gamepad != null) gamepad.SetMotorSpeeds(m_magPower, 0); }
        else { if (gamepad != null) gamepad.SetMotorSpeeds(0, 0); }
        
        //  ベクトルが下向きだったら下降アニメにする
        if (m_jumping &&
            m_rb.velocity.y < 0 &&
            !m_animator.GetBool("Fall")) m_animator.SetBool("Fall", true);

        //  着地中の処理
        if (GroundCheck())
        {
            //  ジャンプ回数のリセット
            m_currentJumpNum = 1;

            //  地上にいる時間の計測
            m_landingTimer += Time.deltaTime;
            //  ジャンプ中ならアニメーションを着地させる
            if (m_jumping && m_rb.velocity.y < 0.01f)
            {
                m_animator.SetBool("Jump", false);
                m_jumping = false;
                m_animator.SetBool("Fall", false);
                m_audioSource.PlayOneShot(m_jumpAudio);
            }
            if (!m_onGround)
            {
                m_onGround = true;
                //  落ちるアニメ
                if (m_animator.GetFloat("Move") > 0.0f)
                {
                    m_walkEffect.Stop();
                    m_audioSource.Stop();
                }
                m_animator.SetFloat("Move", 0.0f);

                //onGroundEffect.Play();
                //  位置計算
                Vector3 iPos = this.transform.position;
                iPos.y -= 1f;
                Instantiate(m_onGroundEffect, iPos, Quaternion.Euler(-90f, 0f, 0f));
            }
        }
        else m_landingTimer = 0f;

        bool deceleration = m_landingTimer > m_landingTime;   //  減速するかどうか

        //  地上でキー入力がされていなければ徐々に減速する
        if (deceleration && Mathf.Abs(m_move) < 0.5f) m_rb.velocity *= new Vector2(m_friction, 1f);
        //  地上で一定以上の速度が出ていたら減速する
        if (deceleration && Mathf.Abs(m_rb.velocity.x) > m_walkMaxSpeed) m_rb.velocity *= new Vector2(m_friction, 1f);

        

        m_move = 0.0f;
        m_climb = 0.0f;

        switch (m_state)
        {
            //  行動状態
            case PlayerState.Move:
                //  コントローラーから入力を受け取る（スティックの上下）
                m_climb = m_controll.Player.Climb.ReadValue<float>();
                //  歩かせる
                Walk();

                //  ジャンプ
                if (m_controll.Player.Jump.WasPressedThisFrame() && m_currentJumpNum > 0 && !m_jumping)
                {
                    m_jumping = true;
                    //  アニメーターの再生
                    m_animator.SetBool("Jump", true);
                    //  ジャンプの高さを一定にするためにy軸のvelocityを0にする
                    m_rb.velocity = new Vector2(m_rb.velocity.x, 0f);
                    //  はしごをつかんでいれば離す
                    m_climbing = false;
                    m_animator.SetBool("Climb", m_climbing);
                    //  velocityにジャンプの力を加える
                    m_rb.AddForce(Vector2.up * m_jumpHeight, ForceMode2D.Impulse);
                    m_audioSource.Stop();
                    m_audioSource.PlayOneShot(m_jumpAudio);
                    m_walkEffect.Stop();
                    
                    //  処理を終わらせる
                    break;
                }
                //  ジャンプの高さをボタンを離したタイミングで変更できるようにする
                if (m_controll.Player.Jump.WasReleasedThisFrame())
                {
                    //  ジャンプ回数を消費
                    m_currentJumpNum--;

                    //  ジャンプで上昇中の時にボタンが離されたら減速させる
                    if (m_rb.velocity.y > 0f) m_rb.velocity = new Vector2(m_rb.velocity.x, m_rb.velocity.y / 2f);
                }

                //  録音
                if (m_controll.Player.Recording.WasPressedThisFrame() && m_currentJumpNum > 0)
                {
                    //  録音状態にする
                    m_state = PlayerState.Rec;
                    //  アニメーターの変更
                    m_animator.SetBool("Rec", true);
                    m_walkEffect.Stop();
                    break;
                }
                //  音を再生する状態にする
                if (m_controll.Player.Play.WasPressedThisFrame() && m_currentJumpNum > 0)
                {
                    //  先頭の音を発射できるか
                    if (m_haveSound.GetAudioClip(1) == null) return;
                    //  再生状態にする
                    m_state = PlayerState.Play;
                    m_walkEffect.Stop();
                    m_audioSource.Stop();
                    m_animator.SetFloat("Move", 0f);
                    //  再生
                    m_haveSound.Play();
                    break;
                }
                //  攻撃する
                if (m_controll.Player.Action.WasPressedThisFrame() && m_currentJumpNum > 0 && !m_climbing && !m_option.GetInputWait())
                {
                    //  攻撃状態へ
                    m_state = PlayerState.Attack;
                    //  攻撃アニメーション
                    m_animator.SetTrigger("Attack");
                    m_walkEffect.Stop();
                    m_audioSource.Stop();
                    //  移動量xをゼロ
                    m_rb.velocity = new Vector2(0.0f, m_rb.velocity.y);
                    break;
                }

                //  再生する音の変更
                if (m_controll.Player.Change.WasPressedThisFrame())
                    m_haveSound.SoundChange();

                break;

            //  再生状態
            case PlayerState.Play:
                //  再生状態を解除する
                if (m_controll.Player.Play.WasReleasedThisFrame())
                {
                    //  動けるようにする
                    m_state = PlayerState.Move;
                   
                    //  止める
                    m_haveSound.Stop();
                    //  処理しない
                    break;
                }

                break;

            //  録音状態
            case PlayerState.Rec:
                //  録音をやめる
                if (m_controll.Player.Recording.WasReleasedThisFrame())
                {
                    //  移動状態
                    m_state = PlayerState.Move;
                    //  アニメーターの変更
                    m_animator.SetBool("Rec", false);
                    //  処理しない
                    break;
                }

                //  現在位置
                Vector2 nowPosition = this.transform.position;
                //  ギミック音のレイヤー
                int layerMask = LayerMask.GetMask("GimmickSE");
                //  Rayを飛ばす
                RaycastHit2D hitObj = Physics2D.CircleCast(nowPosition, m_SECheckRadius, Vector2.zero, 0.0f, layerMask);
                //  Gimmickに当たっているか
                if (hitObj.collider != null)
                {
                    OnRec(hitObj.collider.gameObject);
                    break;
                }

                //  ギミック音のレイヤー
                layerMask = LayerMask.GetMask("SoundChange");
                //  Rayを飛ばす
                hitObj = Physics2D.CircleCast(nowPosition, m_SECheckRadius, Vector2.zero, 0.0f, layerMask);
                //  Gimmickに当たっているか
                if (hitObj.collider != null) OnRec(hitObj.collider.gameObject);

                break;

            //  攻撃状態
            case PlayerState.Attack:
                //  レイを飛ばすタイミング
                if(m_playerAnim.GetSetAttack)
                {
                    //  アニメーションを終了させる
                    m_playerAnim.GetSetAttack = false;
                    //  状態を戻す
                    m_state = PlayerState.Move;

                    //  攻撃位置
                    Vector2 attackPosition = m_attackPoint.position;
                    //  素材固体のレイヤー
                    layerMask = LayerMask.GetMask("MatSolid");
                    //  Rayを飛ばす
                    hitObj = Physics2D.CircleCast(attackPosition, m_attackRayRad, Vector2.zero, 0.0f, layerMask);
                    //  音を鳴らしてあげる
                    if (hitObj.collider != null)
                    {
                        //  再生する
                        hitObj.transform.GetComponent<AudioSource>().Play();
                        //  処理終了
                        break;
                    }

                    //  Switchのレイヤー
                    layerMask = LayerMask.GetMask("Switch");
                    //  Rayを飛ばす
                    hitObj = Physics2D.CircleCast(attackPosition, m_attackRayRad, Vector2.zero, 0.0f, layerMask);
                    //  スウィッチを動かす
                    if (hitObj.collider != null)
                    {
                        hitObj.transform.GetComponent<Switch>().AttackSwitch();
                        break;
                    }

                    //  音変更ギミック
                    layerMask = LayerMask.GetMask("SoundChange");
                    //  Rayを飛ばす
                    hitObj = Physics2D.CircleCast(attackPosition, m_attackRayRad, Vector2.zero, 0.0f, layerMask);
                    //  ヒット
                    if (hitObj.collider != null)
                    {
                        hitObj.transform.GetComponent<SoundChange>().HitSoundChange();
                        break;
                    }

                    //  再生方向変更レイヤー
                    layerMask = LayerMask.GetMask("PlayChange");
                    //  Rayを飛ばす
                    hitObj = Physics2D.CircleCast(attackPosition, m_attackRayRad, Vector2.zero, 0.0f, layerMask);
                    //  ヒット
                    if (hitObj.collider != null)
                    {
                        //  再生方向を変更する
                        m_haveSound.PlayBack();
                        break;
                    }

                    //  物を落とすレイヤー
                    layerMask = LayerMask.GetMask("FallObj");
                    //  Rayを飛ばす
                    hitObj = Physics2D.CircleCast(attackPosition, m_attackRayRad, Vector2.zero, 0.0f, layerMask);
                    //  ヒット
                    if (hitObj.collider != null)
                    {
                        //  音を発生させる
                        hitObj.collider.GetComponent<Fall>().ActionFall();
                        break;
                    }
                    
                }
                
                break;
        }

        //  ジャンプ以外の方法で地面から離れたら
        //  地上ジャンプを無くし、ダッシュできるようにする
        if (GroundExit())
        {
            m_currentJumpNum = 0;
            //  落ちるアニメ
            if (!m_jumping) m_animator.SetFloat("Move", 1.0f);
            m_onGround = false;

            m_walkEffect.Stop();
            m_audioSource.Stop();
        }

        //  はしごの処理
        ClimbingLadder();

        //  beforeGroundの更新
        m_beforeGround = GroundCheck();
    }

    /// <summary>
    /// 着地しているかどうかを判定する
    /// </summary>
    /// <returns>true : 着地している</returns>
    private bool GroundCheck()
    {
        //  現在位置
        Vector2 nowPosition = this.transform.position;

        //  地面のレイヤー
        int layerMask = LayerMask.GetMask("Ground");

        //  Rayを飛ばす
        RaycastHit2D hitObj = Physics2D.CircleCast(nowPosition, m_checkRadius, Vector2.down, m_checkDistance, layerMask);

        //  地面に当たったか確認
        if (hitObj.collider != null)
        {
            //  地面に当たっている
            return true;
        }

        //  箱のレイヤー
        layerMask = LayerMask.GetMask("Box");
        //  Rayを飛ばす
        hitObj = Physics2D.CircleCast(nowPosition, m_checkRadius, Vector2.down, m_checkDistance, layerMask);
        //  箱に当たったか確認
        if (hitObj.collider != null)
        {
            //  箱に当たっている
            return true;
        }

        //  地面のレイヤー
        layerMask = LayerMask.GetMask("FallObj");
        //  Rayを飛ばす
        hitObj = Physics2D.CircleCast(nowPosition, m_checkRadius, Vector2.down, m_checkDistance, layerMask);
        //  箱に当たったか確認
        if (hitObj.collider != null)
        {
            //  箱に当たっている
            return true;
        }

        return false;
    }

    /// <summary>
    /// 地面から離れた瞬間かどうか
    /// </summary>
    /// <returns>true : 地面から離れた瞬間</returns>
    private bool GroundExit()
    {
        bool nowGround = GroundCheck();

        if (m_beforeGround && !nowGround)
        {
            return true;
        }

        return false;
    }

    /// <summary>
    /// 地上の歩き移動
    /// </summary>
    /// <param name="move">キー入力による移動方向</param>
    private void Walk()
    {
        if (m_climbing) return;

        m_move = m_controll.Player.Move.ReadValue<float>();

        //  右移動
        if (m_move > 0 && m_rb.velocity.x < m_walkMaxSpeed) m_rb.velocity += new Vector2(m_walkingAcceleration, 0f);
        //  左移動
        else if (m_move < 0 && m_rb.velocity.x > -m_walkMaxSpeed) m_rb.velocity += new Vector2(-m_walkingAcceleration, 0f);

        //  向いている方向に変更があれば適用する
        if (m_move > 0f && m_direction != 1)
        {
            //  右向き
            m_direction = 1;

            //  向き変え
            m_playerSprite.transform.localScale = new Vector3(Mathf.Abs(m_playerSprite.transform.localScale.x),
                m_playerSprite.transform.localScale.y,
                m_playerSprite.transform.localScale.z);

            //  エフェクト類
            m_walkEffect.transform.localEulerAngles = new Vector3(-90.0f, 0.0f, 0.0f);
        }
        else if (m_move < 0f && m_direction != -1)
        {
            //  左向き
            m_direction = -1;
            //  向き変え
            m_playerSprite.transform.localScale = new Vector3(-Mathf.Abs(m_playerSprite.transform.localScale.x),
                m_playerSprite.transform.localScale.y,
                m_playerSprite.transform.localScale.z);

            //  エフェクト類
            m_walkEffect.transform.localEulerAngles = new Vector3(-90.0f, 0.0f, 180.0f);
        }

        if (!m_onGround) return;
        //  アニメーションの変更
        if (Mathf.Abs(m_move) > 0f)
        {
            if (m_animator.GetFloat("Move") < 0.5f)
            {
                m_walkEffect.Play();
                m_audioSource.Play();
            }
            m_animator.SetFloat("Move", 0.5f);
        }
        else
        {
            if (m_animator.GetFloat("Move") > 0.0f)
            {
                m_walkEffect.Stop();
                m_audioSource.Stop();
            }
            m_animator.SetFloat("Move", 0f);
        }
    }

    public void PlayerReset(Vector3 pos)
    {
        //  位置を戻す
        gameObject.transform.position = pos;
        //  サイズを戻す
        gameObject.transform.localScale = Vector3.one;

        //  アニメーションを戻す
        m_animator.Play("Spawn");

        m_beforeGround = false;
        m_landingTimer = 0f;
        m_haveSound.Init();
        m_direction = 1;
        //  向き変え
        m_playerSprite.transform.localScale = new Vector3(0.5f,
            0.5f,
            gameObject.transform.localScale.z);

        m_playerAnim.GetSetIsStart = false;
        m_playerAnim.GetSetIsGameOver = false;

        m_move = 0.0f;

        m_isDead = false;
        //  アニメーションの再生
        m_animator.SetBool("IsDead", m_isDead);

        //  初期状態:移動
        m_state = PlayerState.Move;

        //  エフェクト類
        m_walkEffect.transform.localEulerAngles = new Vector3(-90.0f, 0.0f, 0.0f);
    }

    //  当たり判定
    private void OnTriggerEnter2D(Collider2D collision)
    {
        //  録音できる状態に入る
        if(collision.gameObject.layer == LayerMask.NameToLayer("GimmickSE"))
        {
            m_mag = true;

            //  表示
            if (m_recordingUI != null)
            {
                m_recordingUI.SetActive(true);
                m_recordingUI.GetComponent<PlayerOnUI>().display = true;
                m_recordingUI.GetComponent<PlayerOnUI>().Start();
            }
        }

        //  ダメージを食らうオブジェクト
        if ((collision.gameObject.CompareTag("DamegeObj") 
            || collision.gameObject.CompareTag("Water")
            || collision.gameObject.CompareTag("Fire"))
            && !m_isDead)
        {
            //  死亡状態
            m_isDead = true;
            //  動きを止める
            m_rb.velocity = Vector3.zero;
            //  アニメーションの再生
            m_animator.SetBool("IsDead", m_isDead);
        }

        //  はしごを上ることが出来る状態かチェックする
        if (collision.transform.CompareTag("Ladder"))
        {
            m_onLadder = true;
        }
    }
        private void OnTriggerExit2D(Collider2D collision)
    {
        //  録音できない状態に入る
        if (collision.gameObject.layer == LayerMask.NameToLayer("GimmickSE"))
        {
            m_mag = false;
            Gamepad gamepad = Gamepad.current;
            if (gamepad != null) gamepad.SetMotorSpeeds(0.0f, 0.0f);
            //  表示
            if (m_recordingUI != null)
            {
                m_recordingUI.GetComponent<PlayerOnUI>().display = false;
            }
        }

        //  はしごから離れたら強制解除
        if (collision.transform.CompareTag("Ladder"))
        {
            m_climbing = false;
            m_onLadder = false;
            //  アニメーターを強制解除
            m_animator.SetBool("Climb", false);
        }
    }

    /// <summary>
    /// はしごを使う処理
    /// </summary>
    private void ClimbingLadder()
    {
        //  はしごを上っている状態かどうかを切り替える
        if (Mathf.Abs(m_climb) > 0.5f && m_onLadder && !m_climbing)
        {
            m_climbing = true;
            //  ジャンプを閉じる
            m_animator.SetBool("Jump", false);
            m_jumping = false;
            m_animator.SetBool("Climb", m_climbing);
            
        }

        //  はしごを上っている状態でなければ処理しない
        if (!m_climbing)
        {
            m_rb.gravityScale = m_gravity;
            return;
        }

        //  ジャンプできる状態にする
        m_currentJumpNum = 1;

        //  梯子を上る処理中なので重力を0にする
        m_rb.gravityScale = 0f;

        //  登る
        if (m_climb > 0.1f)
        {
            m_rb.velocity = Vector2.up * m_climbSpeed;
            m_animator.SetFloat("ClimbSpeed", 1.0f);
        }
        //  降りる
        else if (m_climb < -0.1f)
        {
            m_rb.velocity = Vector2.down * m_climbSpeed;
            m_animator.SetFloat("ClimbSpeed", 1.0f);
        }
        //  操作なし
        else
        {
            m_rb.velocity = Vector2.zero;
            m_animator.SetFloat("ClimbSpeed", 0.0f);
        }
    }

    //  音を録音する
    private void OnRec(GameObject hitObj)
    {
        if(hitObj.TryGetComponent(out GimmickSE gimmickSE))
        {
            //  衝突したオブジェクトのSEを受け取る
            AudioClip hitSE = gimmickSE.GetAudioSource().clip;
            //  衝突したオブジェクトの音の種類を受け取る
            SoundKind sounds = gimmickSE.GetSoundKind();
            //  ロクオンした際のイベント
            gimmickSE.OnEvent();

            //  音が無かったら処理しない
            if (sounds == SoundKind.Over) return;

            //  プレイヤーに音/種類を渡す
            m_haveSound.Recording(hitSE, sounds);
            //  状態を戻す
            m_state = PlayerState.Move;
            //  アニメーターの変更
            m_animator.SetBool("Rec", false);
        }
    }

    public void PlayerClear()
    {
        m_clearTimer += Time.deltaTime;
        if (m_clearTimer > 1.0f) m_clearTimer = 1.0f;
        //  位置移動
        gameObject.transform.position = Vector3.Lerp(m_defPos, m_goalPos, m_clearTimer);
        //  サイズ変更
        gameObject.transform.localScale = Vector3.Lerp(Vector3.one, Vector3.zero, m_clearTimer);
    }
    public void PlayerClearInit(Vector3 gp)
    {
        //  音消す
        m_audioSource.Stop();

        m_defPos = gameObject.transform.position;
        m_goalPos = gp;

        m_clearTimer = 0.0f;
    }

    public bool GetIsStart() { return m_playerAnim.GetSetIsStart; }
    public bool GetIsGameOver() { return m_playerAnim.GetSetIsGameOver; }
}

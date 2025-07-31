using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public class TemaChangeMenu : MonoBehaviour
{
    public Image TemaImage;
    public GameObject LeftButton_Obj;
    public GameObject RightButton_Obj;
    public GameObject ConfirmButton_Obj;
    public GameObject BackButton_Obj;

    public List<Sprite> TemaImageList = new List<Sprite>();
    public delegate void TemaChangeButtonDelegate(int Index);
    public event TemaChangeButtonDelegate OnTemaChange;
    public delegate void TemaCancelButtonDelegate();
    public event TemaCancelButtonDelegate OnTemaCancel;

    MainMenu mainMenu;
    int TemaIndex = 0;
    int currentTemaIndex = 0;

    void Update()
    {
        if (mainMenu && mainMenu.bIsEnabledTemaSelect)
        {
            if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.Space))
            {
                OnClickedConfirm_Btn();
            }
            else if (Input.GetKeyDown(KeyCode.Escape))
            {
                OnClickedBackButton();
            }
            else if (Input.GetKeyDown(KeyCode.LeftArrow))
            {
                OnClickedLeftArrow_Btn();
            }
            else if (Input.GetKeyDown(KeyCode.RightArrow))
            {
                OnClickedRightArrow_Btn();
            }
        }
    }

    public void InitializedTemaChangeMenu(GameObject parent)
    {
        if (parent)
        {
            mainMenu = parent.GetComponent<MainMenu>();
            LeftButton_Obj.GetComponent<Button>().onClick.AddListener(OnClickedLeftArrow_Btn);
            RightButton_Obj.GetComponent<Button>().onClick.AddListener(OnClickedRightArrow_Btn);
            ConfirmButton_Obj.GetComponent<Button>().onClick.AddListener(OnClickedConfirm_Btn);
            BackButton_Obj.GetComponent<Button>().onClick.AddListener(OnClickedBackButton);
            if (TemaImageList.Count > 0)
            {
                TemaImage.sprite = TemaImageList[TemaIndex];
            }
        }
    }

    void OnClickedLeftArrow_Btn()
    {
        if (TemaImageList.Count > 0)
        {
            TemaIndex = Mathf.Clamp(TemaIndex - 1, 0, TemaImageList.Count - 1);
            TemaImage.sprite = TemaImageList[TemaIndex];
            EventSystem.current.SetSelectedGameObject(ConfirmButton_Obj);
        }
    }

    void OnClickedRightArrow_Btn()
    {
        if (TemaImageList.Count > 0)
        {
            TemaIndex = Mathf.Clamp(TemaIndex + 1, 0, TemaImageList.Count - 1);
            TemaImage.sprite = TemaImageList[TemaIndex];
            EventSystem.current.SetSelectedGameObject(ConfirmButton_Obj);
        }
    }

    void OnClickedConfirm_Btn()
    {
        currentTemaIndex = TemaIndex;
        if (TemaImageList.Count > 0)
        {
            TemaImage.sprite = TemaImageList[currentTemaIndex];
        }
        OnTemaChange?.Invoke(currentTemaIndex + 1);
    }

    void OnClickedBackButton()
    {
        TemaImage.sprite = TemaImageList[currentTemaIndex];
        OnTemaCancel?.Invoke();
    }
}

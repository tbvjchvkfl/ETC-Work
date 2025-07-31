using System.Collections;
using TMPro;
using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class MenuButton : MonoBehaviour, IPointerEnterHandler, IPointerExitHandler, ISelectHandler, IDeselectHandler
{
    public TMP_Text ButtonText;
    public int buttonIndex;
    public string ButtonName;

    public delegate void MenuButtonClickedDelegate(TMP_Text TitleString);
    public event MenuButtonClickedDelegate OnMenuButtonClicked;
    
    public delegate void StartButtonClickedDelegate();
    public event StartButtonClickedDelegate OnStartButtonClicked;

    public delegate void TemaSelectButtonClickedDelegate();
    public event TemaSelectButtonClickedDelegate OnTemaSelectButtonClicked;

    Button MenuBtn;
    Animator animationController;

    public void InitializeMenuButton()
    {
        animationController = GetComponent<Animator>();
        MenuBtn = GetComponent<Button>();
        MenuBtn.onClick.AddListener(OnClickedMenuButton);
    }

    void OnClickedMenuButton()
    {
        OnMenuButtonClicked?.Invoke(ButtonText);
        if (ButtonName == "Start Button")
        {
            OnStartButtonClicked?.Invoke();
        }
        else if (ButtonName == "Tema Select Button")
        {
            OnTemaSelectButtonClicked?.Invoke();
        }
        else if (ButtonName == "Exit Button")
        {
            Application.Quit();
        }
    }

    public void OnFocusEnter()
    {
        if (animationController)
        {
            animationController.SetBool("Focus On", true);
        }
    }

    public void OnFocusExit()
    {
        if (animationController)
        {
            animationController.SetBool("Focus On", false);
        }
    }

    public void OnSelect(BaseEventData eventData)
    {
        OnFocusEnter();
    }

    public void OnDeselect(BaseEventData eventData)
    {
        OnFocusExit();
        StartCoroutine(CheckEscapeFocus());
    }

    public void OnPointerEnter(PointerEventData pointerEventData)
    {
        OnFocusEnter();
        EventSystem.current.SetSelectedGameObject(gameObject);
    }

    public void OnPointerExit(PointerEventData pointerEventData)
    {
        OnFocusExit();
    }

    IEnumerator CheckEscapeFocus()
    {
        yield return null;
        if (EventSystem.current.currentSelectedGameObject == null)
        {
            EventSystem.current.SetSelectedGameObject(this.gameObject);
        }
    }
}

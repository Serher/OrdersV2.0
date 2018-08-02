object Form1: TForm1
  Left = 191
  Top = 126
  BorderStyle = bsSingle
  Caption = #1047#1072#1082#1072#1079#1099
  ClientHeight = 763
  ClientWidth = 1289
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Times New Roman'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    1289
    763)
  PixelsPerInch = 96
  TextHeight = 19
  object Label3: TLabel
    Left = 320
    Top = 120
    Width = 41
    Height = 15
    Caption = #1057#1087#1080#1089#1086#1082
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 320
    Top = 520
    Width = 34
    Height = 15
    Caption = #1054#1092#1080#1089':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 320
    Top = 568
    Width = 51
    Height = 15
    Caption = #1057#1095#1077#1090#1072' '#1085#1072':'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 16
    Top = 740
    Width = 66
    Height = 15
    Anchors = [akLeft, akBottom]
    Caption = 'Osipov, v3.0'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 16
    Top = 120
    Width = 49
    Height = 15
    Caption = #1055#1086#1079#1080#1094#1080#1080
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object SG2: TStringGrid
    Left = 944
    Top = 8
    Width = 129
    Height = 81
    TabOrder = 26
    Visible = False
  end
  object LB2: TListBox
    Left = 16
    Top = 504
    Width = 281
    Height = 97
    ItemHeight = 19
    TabOrder = 12
    Visible = False
  end
  object CB2: TComboBox
    Left = 320
    Top = 536
    Width = 281
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    TabOrder = 0
    TabStop = False
  end
  object Memo2: TMemo
    Left = 928
    Top = 24
    Width = 345
    Height = 513
    TabStop = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Bt2: TButton
    Left = 320
    Top = 616
    Width = 281
    Height = 33
    Caption = #1057#1075#1077#1085#1077#1088#1080#1088#1086#1074#1072#1090#1100' '#1087#1080#1089#1100#1084#1086' ->'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    TabStop = False
    OnClick = Bt2Click
  end
  object CB3: TComboBox
    Left = 320
    Top = 584
    Width = 281
    Height = 27
    Style = csDropDownList
    ItemHeight = 19
    TabOrder = 3
    TabStop = False
    Items.Strings = (
      #1040#1083#1100#1090#1072#1075#1077#1085
      #1055#1050#1042#1085#1077#1090
      #1069#1082#1086#1090#1077#1083#1077#1082#1086#1084' '#1055#1086#1076#1086#1083#1100#1089#1082
      #1054#1088#1073#1080#1090#1091)
  end
  object Bt3: TButton
    Left = 1096
    Top = 592
    Width = 177
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1089#1083#1077#1076#1085#1080#1081' '#1079#1072#1082#1072#1079
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    TabStop = False
    OnClick = Bt3Click
  end
  object CheckBox1: TCheckBox
    Left = 1256
    Top = 568
    Width = 17
    Height = 17
    TabStop = False
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object Bt4: TButton
    Left = 1096
    Top = 624
    Width = 177
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1089#1083#1077#1076#1085#1102#1102' '#1087#1086#1079#1080#1094#1080#1102
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    OnClick = Bt4Click
  end
  object Button1: TButton
    Left = 1184
    Top = 8
    Width = 89
    Height = 17
    Caption = #1054#1090#1095#1077#1090#1099
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    TabStop = False
    OnClick = Button1Click
  end
  object SG1: TStringGrid
    Left = 320
    Top = 136
    Width = 281
    Height = 297
    TabStop = False
    ColCount = 3
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing]
    ParentFont = False
    TabOrder = 8
    ColWidths = (
      163
      56
      38)
  end
  object Button2: TButton
    Left = 320
    Top = 432
    Width = 81
    Height = 17
    Caption = #1054#1095#1080#1089#1090#1080#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 9
    TabStop = False
    OnClick = Button2Click
  end
  object GroupBox1: TGroupBox
    Left = 624
    Top = 568
    Width = 281
    Height = 81
    Caption = #1055#1086#1080#1089#1082' '#1087#1086' '#1085#1086#1084#1077#1088#1091' '#1089#1095#1077#1090#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = [fsUnderline]
    ParentFont = False
    TabOrder = 10
    object LE4: TLabeledEdit
      Left = 16
      Top = 50
      Width = 73
      Height = 23
      TabStop = False
      EditLabel.Width = 26
      EditLabel.Height = 15
      EditLabel.Caption = #1057#1095#1077#1090
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 0
      OnKeyPress = LE4KeyPress
    end
    object LE5: TLabeledEdit
      Left = 104
      Top = 48
      Width = 161
      Height = 23
      TabStop = False
      EditLabel.Width = 30
      EditLabel.Height = 15
      EditLabel.Caption = #1047#1072#1082#1072#1079
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 1
    end
  end
  object LB1: TListBox
    Left = 16
    Top = 136
    Width = 281
    Height = 513
    ItemHeight = 19
    PopupMenu = PM1
    TabOrder = 11
    OnClick = LB1Click
    OnDblClick = LB1DblClick
  end
  object GroupBox2: TGroupBox
    Left = 16
    Top = 16
    Width = 585
    Height = 81
    Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1085#1086#1074#1086#1081' '#1087#1086#1079#1080#1094#1080#1080
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    object Label1: TLabel
      Left = 8
      Top = 24
      Width = 86
      Height = 15
      Caption = #1053#1072#1080#1084#1077#1085#1086#1074#1072#1085#1080#1077':'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object CB1: TComboBox
      Left = 8
      Top = 40
      Width = 281
      Height = 27
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = []
      ItemHeight = 19
      ParentFont = False
      TabOrder = 0
      OnEnter = CB1Enter
      OnExit = CB1Exit
    end
    object CB4: TComboBox
      Left = 304
      Top = 40
      Width = 105
      Height = 27
      Style = csDropDownList
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = []
      ItemHeight = 19
      ParentFont = False
      TabOrder = 1
      Items.Strings = (
        #1096#1090'.'
        #1073#1091#1093#1090
        #1091#1087'.')
    end
    object Bt1: TButton
      Left = 424
      Top = 40
      Width = 153
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Bt1Click
    end
  end
  object Panel1: TPanel
    Left = 624
    Top = 136
    Width = 281
    Height = 297
    TabOrder = 14
    object Label6: TLabel
      Left = 9
      Top = 40
      Width = 32
      Height = 15
      Caption = #1057#1095#1077#1090#1072
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object LE1: TLabeledEdit
      Left = 96
      Top = 8
      Width = 81
      Height = 23
      TabStop = False
      Ctl3D = True
      EditLabel.Width = 45
      EditLabel.Height = 15
      EditLabel.Caption = #1047#1072#1082#1072#1079' '#8470
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpLeft
      LabelSpacing = 10
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 0
      OnKeyPress = LE1KeyPress
    end
    object Memo3: TMemo
      Left = 8
      Top = 56
      Width = 265
      Height = 161
      TabStop = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object LE2: TLabeledEdit
      Left = 8
      Top = 234
      Width = 113
      Height = 23
      TabStop = False
      EditLabel.Width = 71
      EditLabel.Height = 15
      EditLabel.Caption = #1053#1086#1084#1077#1088' '#1089#1095#1077#1090#1072
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 2
      OnEnter = LE2Enter
    end
    object LE3: TLabeledEdit
      Left = 160
      Top = 234
      Width = 113
      Height = 23
      TabStop = False
      EditLabel.Width = 26
      EditLabel.Height = 15
      EditLabel.Caption = #1044#1072#1090#1072
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 3
    end
    object Bt5: TButton
      Left = 88
      Top = 264
      Width = 113
      Height = 25
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      TabStop = False
      OnClick = Bt5Click
    end
  end
  object CB5: TComboBox
    Left = 624
    Top = 24
    Width = 281
    Height = 31
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -21
    Font.Name = 'Times New Roman'
    Font.Style = []
    ItemHeight = 23
    ParentFont = False
    TabOrder = 15
    OnSelect = CB5Select
  end
  object Button3: TButton
    Left = 520
    Top = 432
    Width = 81
    Height = 17
    Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 16
    OnClick = Button3Click
  end
  object mysql: TCheckBox
    Left = 152
    Top = 732
    Width = 65
    Height = 17
    Anchors = [akLeft, akBottom]
    Caption = 'MySQL'
    Checked = True
    Enabled = False
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 17
  end
  object Button4: TButton
    Left = 624
    Top = 64
    Width = 75
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 18
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 824
    Top = 64
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1080#1090#1100
    TabOrder = 19
    OnClick = Button5Click
  end
  object Panel2: TPanel
    Left = 1016
    Top = 592
    Width = 25
    Height = 25
    Color = clBackground
    TabOrder = 20
    Visible = False
    DesignSize = (
      25
      25)
    object Label8: TLabel
      Left = 1
      Top = 32
      Width = 399
      Height = 24
      Alignment = taCenter
      AutoSize = False
      Caption = #1059#1074#1077#1088#1077#1085#1099'?'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Button6: TButton
      Left = 32
      Top = 80
      Width = 75
      Height = 25
      Caption = #1044#1072
      TabOrder = 0
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = -80
      Top = -24
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1053#1077#1090
      TabOrder = 1
      OnClick = Button7Click
    end
  end
  object Panel3: TPanel
    Left = 1016
    Top = 624
    Width = 25
    Height = 25
    BevelWidth = 5
    Color = clAppWorkSpace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 21
    Visible = False
    DesignSize = (
      25
      25)
    object Ed1: TEdit
      Left = 16
      Top = 24
      Width = 249
      Height = 27
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnKeyPress = Ed1KeyPress
    end
    object LE6: TLabeledEdit
      Left = 16
      Top = 80
      Width = 113
      Height = 23
      EditLabel.Width = 98
      EditLabel.Height = 15
      EditLabel.Caption = #1058#1077#1082#1091#1097#1072#1103' '#1087#1086#1079#1080#1094#1080#1103
      EditLabel.Font.Charset = RUSSIAN_CHARSET
      EditLabel.Font.Color = clWindowText
      EditLabel.Font.Height = -13
      EditLabel.Font.Name = 'Times New Roman'
      EditLabel.Font.Style = []
      EditLabel.ParentFont = False
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      LabelPosition = lpAbove
      LabelSpacing = 3
      ParentFont = False
      TabOrder = 1
      OnKeyPress = LE6KeyPress
    end
    object BitBtn1: TBitBtn
      Left = 16
      Top = -16
      Width = 113
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1089#1087#1080#1089#1086#1082
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clGreen
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = BitBtn1Click
    end
    object BitBtn2: TBitBtn
      Left = -104
      Top = -16
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1047#1072#1082#1088#1099#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = BitBtn2Click
    end
    object UD1: TUpDown
      Left = 240
      Top = 64
      Width = 25
      Height = 41
      Min = 0
      Increment = -1
      Position = 0
      TabOrder = 4
      Wrap = False
      OnClick = UD1Click
    end
  end
  object Button8: TButton
    Left = 728
    Top = 64
    Width = 65
    Height = 25
    Caption = #1048#1085#1092#1086
    TabOrder = 22
    OnClick = Button8Click
  end
  object Panel4: TPanel
    Left = 984
    Top = 592
    Width = 25
    Height = 25
    Color = clAppWorkSpace
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 23
    Visible = False
    DesignSize = (
      25
      25)
    object Label9: TLabel
      Left = -56
      Top = 22
      Width = 47
      Height = 15
      Anchors = [akTop, akRight]
      Caption = #1040#1082#1090#1080#1074#1085#1072
    end
    object LE7: TLabeledEdit
      Left = 16
      Top = 40
      Width = 217
      Height = 23
      EditLabel.Width = 56
      EditLabel.Height = 15
      EditLabel.Caption = #1050#1086#1084#1087#1072#1085#1080#1103
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 0
    end
    object LE8: TLabeledEdit
      Left = 16
      Top = 88
      Width = 217
      Height = 23
      EditLabel.Width = 59
      EditLabel.Height = 15
      EditLabel.Caption = #1052#1077#1085#1077#1076#1078#1077#1088
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
    end
    object LE9: TLabeledEdit
      Left = 16
      Top = 136
      Width = 217
      Height = 23
      EditLabel.Width = 31
      EditLabel.Height = 15
      EditLabel.Caption = 'e-mail'
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
    end
    object ChB1: TCheckBox
      Left = -4
      Top = 20
      Width = 17
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'ChB1'
      TabOrder = 3
    end
    object BitBtn3: TBitBtn
      Left = 16
      Top = -8
      Width = 75
      Height = 25
      Anchors = [akLeft, akBottom]
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clGreen
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = BitBtn3Click
    end
    object BitBtn4: TBitBtn
      Left = -64
      Top = -8
      Width = 75
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1054#1090#1084#1077#1085#1072
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = BitBtn4Click
    end
  end
  object Memo1: TMemo
    Left = 16
    Top = 664
    Width = 1257
    Height = 65
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 24
  end
  object ChB2: TCheckBox
    Left = 272
    Top = 736
    Width = 65
    Height = 17
    Caption = 'Network'
    Checked = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 25
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'FILE NAME=D:\C++\Borland Projects\Manual tests\OrdersV2.0\Orders' +
      'Connection.udl'
    LoginPrompt = False
    Provider = 
      'D:\C++\Borland Projects\Manual tests\OrdersV2.0\OrdersConnection' +
      '.udl'
    Left = 952
    Top = 624
  end
  object ADOQuery1: TADOQuery
    Parameters = <>
    Left = 952
    Top = 592
  end
  object PM1: TPopupMenu
    Left = 984
    Top = 624
    object N1: TMenuItem
      Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1089#1087#1080#1089#1082#1072
      OnClick = N1Click
    end
  end
  object IdTCPClient1: TIdTCPClient
    Host = '10.210.0.21'
    Port = 37111
    Left = 1056
    Top = 624
  end
end

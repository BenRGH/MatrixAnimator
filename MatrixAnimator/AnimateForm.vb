Public Class AnimateForm
    'Global vars
    Dim frameCount As Integer = 0
    Dim anim As New System.Text.StringBuilder() 'Final animation !not stringified!

    Private Sub ExportBtn_Click(sender As Object, e As EventArgs) Handles ExportBtn.Click

        '                                           j                   i
        '                                A  B  C  D  E  F  G  H
        Dim matrix = New Integer(7, 7) {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0}}

        Dim i As Integer = 7
        Dim j As Integer = 7
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                'For some reason this reads from bottom right to top left
                System.Console.Write(ctrl.Name + " ")
                System.Console.WriteLine(DirectCast(ctrl, CheckBox).Checked)

                'See if it's checked
                If DirectCast(ctrl, CheckBox).Checked Then
                    'Add 1 to matrix in relevant pos
                    matrix(j, i) = 1
                Else
                    'do something else
                    matrix(j, i) = 0
                End If

                'Keeping track of the pos
                If j = 0 Then
                    If Not i = 0 Then
                        i -= 1 'Goes up
                        j = 7 'Start from right again
                    End If
                Else
                    j -= 1 'Goes left
                End If

            End If
        Next



        Dim sb As New System.Text.StringBuilder()
        sb.Append("{")
        For y = 0 To 7
            If y = 0 Then
                sb.Append("B")
            Else
                sb.Append(",B")
            End If

            For x = 0 To 7
                sb.Append(matrix(x, y).ToString())
            Next
        Next
        sb.Append("}")

        Dim matrixStr As String = sb.ToString

        'Output to single pattern textbox
        OutputTxt.Text = (matrixStr)
        'Increment frame count
        frameCount += 1
        FrameCnt.Text = frameCount.ToString()
        'Copy to clipboard
        Clipboard.SetText(matrixStr)

    End Sub

    Private Sub ClearBtn_Click(sender As Object, e As EventArgs) Handles ClearBtn.Click
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                DirectCast(ctrl, CheckBox).Checked = False
            End If
        Next
    End Sub

    Private Sub AddFrameBtn_Click(sender As Object, e As EventArgs) Handles AddFrameBtn.Click

        '                                           j                   i
        '                                A  B  C  D  E  F  G  H
        Dim matrix = New Integer(7, 7) {{0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0}}

        Dim i As Integer = 7
        Dim j As Integer = 7
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                'For some reason this reads from bottom right to top left
                System.Console.Write(ctrl.Name + " ")
                System.Console.WriteLine(DirectCast(ctrl, CheckBox).Checked)

                'See if it's checked
                If DirectCast(ctrl, CheckBox).Checked Then
                    'Add 1 to matrix in relevant pos
                    matrix(j, i) = 1
                Else
                    'do something else
                    matrix(j, i) = 0
                End If

                'Keeping track of the pos
                If j = 0 Then
                    If Not i = 0 Then
                        i -= 1 'Goes up
                        j = 7 'Start from right again
                    End If
                Else
                    j -= 1 'Goes left
                End If

            End If
        Next



        Dim sb As New System.Text.StringBuilder()
        sb.Append("{")
        For y = 0 To 7
            If y = 0 Then
                sb.Append("B")
            Else
                sb.Append(",B")
            End If

            For x = 0 To 7
                sb.Append(matrix(x, y).ToString())
            Next
        Next
        sb.Append("},\" & vbCrLf)

        Dim matrixStr As String = sb.ToString

        'Add current frame to animation string
        anim.Append(matrixStr)
        'Increment frame count
        frameCount += 1
        FrameCnt.Text = frameCount.ToString()


    End Sub

    Private Sub ExportAnimBtn_Click(sender As Object, e As EventArgs) Handles ExportAnimBtn.Click

        If anim.Length > 0 Then
            anim.Length = anim.Length - 4 'Remove arduino newline fluff
        End If

        'Set the final output to the animation textbox
        Dim final As String
        final = "int frames = " & frameCount & ";" & vbCrLf & "byte anim[frames][8]=\" & vbCrLf & "{" & anim.ToString() & "};"
        OutputFrame.Text = final
        'Copy to clipboard
        Clipboard.SetText(final)
    End Sub

    Private Sub ClearAnimBtn_Click(sender As Object, e As EventArgs) Handles ClearAnimBtn.Click
        anim.Clear()
        frameCount = 0
        FrameCnt.Text = 0
        OutputFrame.Text = ""
    End Sub

    Private Sub FillBtn_Click(sender As Object, e As EventArgs) Handles FillBtn.Click
        For Each ctrl As Control In CheckboxPnl.Controls
            If TypeOf ctrl Is CheckBox Then
                DirectCast(ctrl, CheckBox).Checked = True
            End If
        Next
    End Sub

    Private Sub AddTextBtn_Click(sender As Object, e As EventArgs) Handles AddTextBtn.Click
        'Long sub that provides basic alphabet and numbers
        If IsAlphaNum(TextEntry.Text) Then

        End If
    End Sub

    Private Function IsAlphaNum(ByVal strInputText As String) As Boolean
        'Inspired by https://www.codeproject.com/Questions/414509/how-to-check-is-alphanumeric

        Dim IsAlpha As Boolean = False
        If System.Text.RegularExpressions.Regex.IsMatch(strInputText, "^[a-zA-Z0-9]+$") Then
            IsAlpha = True
        Else
            IsAlpha = False
        End If
        Return IsAlpha
    End Function
End Class

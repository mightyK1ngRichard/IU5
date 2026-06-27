function factorial(N) {
    if (N == 0)
        return 1;
    return N ? N * factorial(N - 1) : 1;
}

function P0zn(Ck, N, psi) {
    var result = 0;
    var i;
    var j;

    for (i = 0; i <= Ck; i++)
    {
        result = result + ((factorial(N)*Math.pow(psi, i)) / (factorial(i)*factorial(N-i)));
    };
    for (j = Ck+1; j <= N; j++)
    {
        result = result + ((factorial(N)*Math.pow(psi, j)) / (Math.pow(Ck,j-Ck)*factorial(Ck)*factorial(N-j)));
    };
    return result;
}

function findPk1(P0, i, N, psi){
    return (((factorial(N)*Math.pow(psi, i)) / (factorial(i)*factorial(N-i))) * P0);
}

function findPk2(P0, Ck, i, N, psi){
    return ( (factorial(N)*Math.pow(psi, i)) / (Math.pow(Ck,i-Ck)*factorial(Ck)*factorial(N-i)) ) * P0;
}

function findQ(P0, Ck, N, psi){
    var result= 0;
    var i;
    for (i = Ck; i <= N; i++){
        result = result + (i-Ck) * (findPk2(P0, Ck, i, N, psi));
    }
    return result;
}

function findL(P0, Ck, N, psi){
    var result = 0;
    var i;
    for (i = 1; i < Ck; i++) {
        result = result + i * (findPk1(P0, i, N, psi));
    }
    for (i = Ck; i <= N; i++) {
        result = result + i * (findPk2(P0, Ck, i, N, psi));
    }
    return result;
}

$("#calculate").click(function(){
    var tno = + $("#tno").val();
    var to = + $("#to").val();
    var N = + $("#N").val();
    var C1 = + $("#C1").val();
    var C2 = + $("#C2").val();
    var C3 = + $("#C3").val();
    var S1 = + $("#S1").val();
    var S = + $("#S").val();
    var znak = + $("#znak").val();

    if ((C1 < 0) || (C1 > 100))
    {
        $("#err").html("ОШИБКА: Не выполняется условие 0 ≤ C<sub>1</sub> ≤ 100! Измените значение C<sub>1</sub>");
        document.getElementById("outTable").style.visibility = "hidden";
        if (C2 && C3)
        {
            document.getElementById("bottomSector").style.display = "none";
            document.getElementById("bottomSector").style.visibility = "hidden";
        }
    }
    else
    {
        if ((C2 < 0) || (C2 > 100))
        {
            $("#err").html("ОШИБКА: Не выполняется условие 0 ≤ C<sub>2</sub> ≤ 100! Измените значение C<sub>2</sub>");
            document.getElementById("outTable").style.visibility = "hidden";
            document.getElementById("bottomSector").style.display = "none";
            document.getElementById("bottomSector").style.visibility = "hidden";
        }
        else
        {
            if ((C3 < 0) || (C3 > 100))
            {
                $("#err").html("ОШИБКА: Не выполняется условие 0 ≤ C<sub>3</sub> ≤ 100! Измените значение C<sub>3</sub>");
                document.getElementById("outTable").style.visibility = "hidden";
                document.getElementById("bottomSector").style.display = "none";
                document.getElementById("bottomSector").style.visibility = "hidden";
            }
            else
            {
                $("#err").html("");
                $("head").append("<style> .tdOutHead, .tdOutParam, .tdOutObozn, .tdOutValRazm {border: 2px solid #CCCCCC} .fracUnderlineOut{border-bottom: 1px solid black}</style>");
                document.getElementById("outTable").style.display = "block";
                document.getElementById("outTable").style.visibility = "visible";
                if (document.getElementById("bottomSector"))
                {
                    document.getElementById("bottomSector").style.display = "block";
                    document.getElementById("bottomSector").style.visibility = "visible";
                }
                var muno = Math.pow(tno, -1);
                var muo = Math.pow(to, -1);
                var psi = muno / muo

                var P0 = [Math.pow(P0zn(C1, N, psi), -1), Math.pow(P0zn(C2, N, psi), -1), Math.pow(P0zn(C3, N, psi), -1)]
                var Q = [findQ(P0[0], C1, N, psi), findQ(P0[1], C2, N, psi), findQ(P0[2], C3, N, psi)]
                var L = [findL(P0[0], C1, N, psi), findL(P0[1], C2, N, psi), findL(P0[2], C3, N, psi)]
                var U = [L[0]-Q[0], L[1]-Q[1], L[2]-Q[2]]
                var roo = [U[0]/C1, U[1]/C2, U[2]/C3]
                var Tr = [(L[0]*tno)/(N-L[0]), (L[1]*tno)/(N-L[1]), (L[2]*tno)/(N-L[2])]
                var W = [Tr[0]-to, Tr[1]-to, Tr[2]-to]
                var Tc = [Tr[0]+tno, Tr[1]+tno, Tr[2]+tno]
                var roe = [tno/Tc[0], tno/Tc[1], tno/Tc[2]]
                var n = [N-L[0], N-L[1], N-L[2]]
                var f = [(C1*tno)/(N*to), (C2*tno)/(N*to), (C3*tno)/(N*to)]
                var Y = [C1*S1+L[0]*S, C2*S1+L[1]*S, C3*S1+L[2]*S]


                $("#muno").html(muno.toFixed(znak));
                $("#muo").html(muo.toFixed(znak));
                $("#psi").html(psi.toFixed(znak));

                $("#calcC1").html(C1);
                $("#calcC2").html(C2);
                $("#calcC3").html(C3);

                $("#P01").html(P0[0].toFixed(znak));
                $("#P02").html(P0[1].toFixed(znak));
                $("#P03").html(P0[2].toFixed(znak));

                $("#Q1").html(Q[0].toFixed(znak));
                $("#Q2").html(Q[1].toFixed(znak));
                $("#Q3").html(Q[2].toFixed(znak));

                $("#L1").html(L[0].toFixed(znak));
                $("#L2").html(L[1].toFixed(znak));
                $("#L3").html(L[2].toFixed(znak));

                $("#U1").html(U[0].toFixed(znak));
                $("#U2").html(U[1].toFixed(znak));
                $("#U3").html(U[2].toFixed(znak));

                $("#roo1").html(roo[0].toFixed(znak));
                $("#roo2").html(roo[1].toFixed(znak));
                $("#roo3").html(roo[2].toFixed(znak));

                $("#Tr1").html(Tr[0].toFixed(znak));
                $("#Tr2").html(Tr[1].toFixed(znak));
                $("#Tr3").html(Tr[2].toFixed(znak));

                $("#W1").html(W[0].toFixed(znak));
                $("#W2").html(W[1].toFixed(znak));
                $("#W3").html(W[2].toFixed(znak));

                $("#Tc1").html(Tc[0].toFixed(znak));
                $("#Tc2").html(Tc[1].toFixed(znak));
                $("#Tc3").html(Tc[2].toFixed(znak));

                $("#roe1").html(roe[0].toFixed(znak));
                $("#roe2").html(roe[1].toFixed(znak));
                $("#roe3").html(roe[2].toFixed(znak));

                $("#n1").html(n[0].toFixed(znak));
                $("#n2").html(n[1].toFixed(znak));
                $("#n3").html(n[2].toFixed(znak));

                $("#f1").html(f[0].toFixed(znak));
                $("#f2").html(f[1].toFixed(znak));
                $("#f3").html(f[2].toFixed(znak));

                $("#Y1").html(Y[0].toFixed(znak));
                $("#Y2").html(Y[1].toFixed(znak));
                $("#Y3").html(Y[2].toFixed(znak));

                document.getElementById("Y1").style.backgroundColor = "#f6f9fa";

                if (Y[1] && Y[2]) 
                {
                    document.getElementById("Y2").style.backgroundColor = "#f6f9fa";
                    document.getElementById("Y3").style.backgroundColor = "#f6f9fa";
                    var minY = Math.min(Y[0], Y[1], Y[2])
                    if (minY === Y[0])
                    {
                        document.getElementById("Y1").style.backgroundColor = "lightgoldenrodyellow";
                    }
                    if (minY === Y[1])
                    {
                        document.getElementById("Y2").style.backgroundColor = "lightgoldenrodyellow";
                    }
                    if (minY === Y[2])
                    {
                        document.getElementById("Y3").style.backgroundColor = "lightgoldenrodyellow";
                    }
                }
            }
        }
    }

    if (document.getElementById("graph") && (document.getElementById("bottomSector").style.display != "none"))
    {
        $("#graph").html("");

        var chart = anychart.line([
            {x: C1, value: Y[0]},
            {x: C2, value: Y[1]},
            {x: C3, value: Y[2]}
          ]);
         
          chart.background({fill: "#F6F9FA"});
      
          var xLabels = chart.xAxis().labels();
          xLabels.fontSize(16);
          xLabels.fontColor("black");
      
          var yLabels = chart.yAxis().labels();
          yLabels.fontSize(16);
          yLabels.fontColor("black");
      
          var xTitle = chart.xAxis().title();
          xTitle.enabled(true);
          xTitle.text("C [чел.]");
          xTitle.align("right");
          xTitle.orientation("bottom");
          xTitle.fontSize(16);
          xTitle.fontColor("black");
      
          var yTitle = chart.yAxis().title();
          yTitle.enabled(true);
          yTitle.text("Y [руб./час]");
          yTitle.align("left");
          yTitle.orientation("top");
          yTitle.fontSize(16);
          yTitle.fontColor("black");
      
          chart.container("graph").draw();
      
          $(".anychart-credits").hide();
    }
})
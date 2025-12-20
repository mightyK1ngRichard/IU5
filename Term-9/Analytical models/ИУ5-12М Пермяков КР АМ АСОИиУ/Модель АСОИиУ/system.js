function findLambdaF1(K1, tk, C, beta, tpr, m, td, N){
    return (K1 * Math.min((1 / (2 * tk)), (C / (beta * tpr)), (1 / (beta * (1 / m) * td))) * ((N - 1) / (N)))
}

function findTknl(tk, f1){
    return ((2 * tk) / (1 - 2 * f1 * tk))
}

function findTpr(beta, tpr, C, f1){
    return ((beta * tpr) / (1 - Math.pow(beta * f1 * tpr / C, C)))
}

function findTd(beta, td, m, f1){
    return( (beta * td) / (1 - beta * (1 / m) * f1 * td))
}

function findLambdaF(N, T0, Tr, Tkn, Tpr, Td){
    return ((N - 1) / (T0 + Tr + Tkn + Tpr + Td))
}


$("#calculate").click(function(){
    var N = + $("#N").val();
    var T0 = + $("#T0").val();
    var Tr = + $("#Tr").val();
    var tk1 = + $("#tk1").val();
    var tk2 = + $("#tk2").val();
    var C = + $("#C").val();
    var tpr = + $("#tpr").val();
    var m = + $("#m").val();
    var td = + $("#td").val();
    var p = + $("#p").val();
    var znak = + $("#znak").val();

    var K1 = + $("#K1").val();
    var K2 = + $("#K2").val();
    var delta = + $("#delta").val();

    if ((K1 < 0.9) || (K1 > 0.999995))
    {
        $("#err").html("ОШИБКА: Не выполняется условие 0.9 ≤ K<sub>1</sub> ≤ 0.999995! Измените значение для K<sub>1</sub>");
        document.getElementById("outTable").style.display = "none";
        document.getElementById("outTable").style.visibility = "hidden";
    }
    else
    {
        if ((K2 < 10) || (K2 > 100000))
        {
            $("#err").html("ОШИБКА: Не выполняется условие 10 ≤ K<sub>2</sub> ≤ 100 000! Измените значение для K<sub>2</sub>");
            document.getElementById("outTable").style.display = "none";
            document.getElementById("outTable").style.visibility = "hidden";
        }
        else
        {
            if ((delta < 0.000001) || (delta > 0.9))
            {
                $("#err").html("ОШИБКА: Не выполняется условие 0.000001 ≤ Δ ≤ 0.9! Измените значение для Δ");
                document.getElementById("outTable").style.display = "none";
                document.getElementById("outTable").style.visibility = "hidden";
            }
            else
            {
                $("#err").html("");
                $("head").append("<style> .tdOutHead, .tdOutParam, .tdOutObozn, .tdOutValRazm {border: 2px solid #CCCCCC} .fracUnderlineOut{border-bottom: 1px solid black}</style>");
                document.getElementById("outTable").style.display = "block";
                document.getElementById("outTable").style.visibility = "visible";
                
                var tk = 0.5 * (tk1 + tk2);
                var beta = 1 / (1 - p);

                var lambdaF1 = findLambdaF1(K1, tk, C, beta, tpr, m, td, N);
                var lambdaStart = lambdaF1;
                var lambdaF;

                var iter = 0;

                var Tkn;
                var Tpr;
                var Td;

                while(true)
                {
                    iter=iter+1;
                    Tkn = findTknl(tk, lambdaF1);
                    Tpr = findTpr(beta, tpr, C, lambdaF1);
                    Td = findTd(beta, td, m, lambdaF1);
                    lambdaF = findLambdaF(N, T0, Tr, Tkn, Tpr, Td);
                    if (((Math.abs(lambdaF1 - lambdaF) / lambdaF) < delta) || (iter === 999)) {
                        break;
                    }
                    lambdaF1 = lambdaF1 - (lambdaF1 - lambdaF) / K2;
                }

                var Tcl = (N - 1) / lambdaF;
                var Trk = Tcl - Tr;
                var roRS = (T0 + Tr) / Tcl;
                var roP = Tr / Tcl;
                var KRS = N * (T0 + Tr) / Tcl;
                var roK = 2 * (N / Tcl) * tk;
                var roPr = beta * (N / Tcl) * tpr / C;
                var roD = beta * (N / Tcl) * (1 / m) * td;

                $("#roRS").html(roRS.toFixed(znak));
                $("#roP").html(roP.toFixed(znak));
                $("#KRS").html(KRS.toFixed(znak));
                $("#roK").html(roK.toFixed(znak));
                $("#roPr").html(roPr.toFixed(znak));
                $("#roD").html(roD.toFixed(znak));
                $("#Tcl").html(Tcl.toFixed(znak));
                $("#Trk").html(Trk.toFixed(znak));
                $("#lambdaF1").html(lambdaStart.toFixed(znak));
                $("#lambdaF").html(lambdaF.toFixed(znak));
                $("#iter").html(iter);
            }
        }
    }
})